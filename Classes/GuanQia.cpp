//
//  GuanQia.cpp
//  sanxiao
//
//  Created by MAC on 2018/5/29.
//
//

#include "GuanQia.hpp"
//using namespace cocos2d::ui;
//using namespace std;
//USING_NS_CC;
Scene* xuanguan::createScene()
{
    auto scene = Scene::create();
    auto layer = xuanguan::create();
    scene->addChild(layer);
    return scene;
}
bool xuanguan::init()
{
    if (!Layer::init())
    {
        return false;
    }
    Jsonjiexi();
    auto node = CSLoader::createNode("Layer3.csb");
    this->addChild(node);
//    chushihua();
    auto list = node->getChildByName<cocos2d::ui::ScrollView*>("ScrollView_1");
    for (int i = 1; i<=6; ++i) {
        string str = StringUtils::format("Button_%d",i-1);
        auto bt1 = list->cocos2d::Node::getChildByName<Button*>(str);
        bt1->setEnabled(!islock[i-1]);
        bt1->addClickEventListener([=](Ref*sender){
        auto scene = Game::createScene(i);//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
        });
    }
    return true;
}
void xuanguan::fileCopy()//文件拷贝
{
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径
    string jsonPath = path+string("charpter1.json");
    //拼接路径
    cout<<"可读写文件路径："<<jsonPath<<endl;
    //获取Resource里的chapter.json的路径
    string path2 = FileUtils::getInstance()->fullPathForFilename("charpter1.json");
    //保存
    if (!FileUtils::getInstance()->isFileExist(jsonPath)) {
        string filecontents = FileUtils::getInstance()->getStringFromFile(path2);
        FILE*file = fopen(jsonPath.c_str(), "w");//打开文件，可写
        if (file) {
            fputs(filecontents.c_str(),file);//从缓存输出到文件
            fclose(file);//关闭文件
        }
    }
}
void xuanguan::Jsonjiexi()//解析文件
{
    fileCopy();
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径下面charpter.json文件内容
    string jsonPath = path+string("charpter1.json");             //拼接路径

    string data = FileUtils::getInstance()->getStringFromFile(jsonPath);//从文件获取字符串
    Document doc;                                      //文档
    doc.Parse<kParseDefaultFlags>(data.c_str());       //解析文档
    if (doc.HasParseError())//如果解析错误
    {
        log("json error!\n");//输出提示
        return;//返回
    }
    if (doc.HasMember("gameCharpter"))//如果有gameCharpter
    {
        //for循环，外层循环章节数，内层循环关卡数
        for (int i = 0; i<doc["gameCharpter"].Size();++i) {
            rapidjson::Value& _case = doc["gameCharpter"][i]["Case"];//获取Case
            for (int j = 0; j<_case.Size(); ++j) {
                islock[j] = _case[j]["isLock"].GetBool();//获取关卡状态
                cout<<islock[j]<<endl;
            }
        }
    }
}

