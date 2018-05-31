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
    
    auto node = CSLoader::createNode("Layer3.csb");
    this->addChild(node);
//    chushihua();
    auto list = node->getChildByName<cocos2d::ui::ScrollView*>("ScrollView_1");
    auto bt1 = list->cocos2d::Node::getChildByName<Button*>("Button_0");
    auto bt2 = list->cocos2d::Node::getChildByName<Button*>("Button_1");
    auto bt3 = list->cocos2d::Node::getChildByName<Button*>("Button_2");
    auto bt4 = list->cocos2d::Node::getChildByName<Button*>("Button_3");
    auto bt5 = list->cocos2d::Node::getChildByName<Button*>("Button_4");
    auto bt6 = list->cocos2d::Node::getChildByName<Button*>("Button_4_6");
    bt1->setEnabled(!islock1);
    bt2->setEnabled(!islock2);
    bt3->setEnabled(!islock3);
    bt4->setEnabled(!islock4);
    bt5->setEnabled(!islock5);
    bt6->setEnabled(!islock6);

    bt1->addClickEventListener([](Ref*sender){
        auto scene = Game::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    bt2->addClickEventListener([](Ref*sender){
        auto scene = Game::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    bt3->addClickEventListener([](Ref*sender){
        auto scene = Game::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    bt4->addClickEventListener([](Ref*sender){
        auto scene = Game::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    bt5->addClickEventListener([](Ref*sender){
        auto scene = Game::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    bt6->addClickEventListener([](Ref*sender){
        auto scene = Game::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });


    
    return true;
}
//初始化
/*void xuanguan::chushihua()
{
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径下面charpter.json文件内容
    string jsonPath = path+string("charpter1.json");
    //拼接路径
    string data = FileUtils::getInstance()->fullPathForFilename("charpter1.json");
    if (!FileUtils::getInstance()->isFileExist(jsonPath))
    {
        string filecon = FileUtils::getInstance()->getStringFromFile(data);
        FILE*file = fopen(jsonPath.c_str(), "w");
        if (file)
        {
            fputs(filecon.c_str(), file);
            
            fclose(file);
        }
    }
    //解析
    string dd = FileUtils::getInstance()->getStringFromFile(jsonPath);
    Document doc;//定义文件
    doc.Parse<kParseDefaultFlags>(dd.c_str());
    if (doc.HasParseError()) {
        log("error");
        return;
    }
    rapidjson::Value& gameCharpter = doc["gameCharpter"];
    rapidjson::Value& _element = gameCharpter[0];
    rapidjson::Value& Charpter = _element["Case"][0];
    rapidjson::Value& isLock = Charpter["isLock"];
//    rapidjson::Value& HightScore = Charpter["HighScore"];
//    rapidjson::Value& case1 = Charpter["case"];
    islock1= isLock.GetBool();
    
    
    rapidjson::Value& Charpter1 = _element["Case"][1];
    rapidjson::Value& isLock11 = Charpter1["isLock"];
//    rapidjson::Value& HightScore1 = Charpter1["HighScore"];
//    rapidjson::Value& case2 = Charpter1["case"];
    islock2 = isLock11.GetBool();
    
    
    rapidjson::Value& Charpter2 = _element["Case"][2];
    rapidjson::Value& isLock12 = Charpter2["isLock"];
//    rapidjson::Value& HightScore2 = Charpter2["HighScore"];
//    rapidjson::Value& case3 = Charpter2["case"];
    islock3 = isLock12.GetBool();
    
    
    rapidjson::Value& Charpter3 = _element["Case"][3];
    rapidjson::Value& isLock13 = Charpter3["isLock"];
//    rapidjson::Value& HightScore3 = Charpter3["HighScore"];
//    rapidjson::Value& case4 = Charpter3["case"];
    islock4 = isLock13.GetBool();
    
    
    rapidjson::Value& Charpter4 = _element["Case"][4];
    rapidjson::Value& isLock14 = Charpter4["isLock"];
//    rapidjson::Value& HightScore4 = Charpter4["HighScore"];
//    rapidjson::Value& case5 = Charpter4["case"];
    islock5 = isLock14.GetBool();
    
    
    rapidjson::Value& Charpter5 = _element["Case"][5];
    rapidjson::Value& isLock15 = Charpter5["isLock"];
//    rapidjson::Value& HightScore5 = Charpter5["HighScore"];
//    rapidjson::Value& case6 = Charpter5["case"];
    islock6 = isLock15.GetBool();
    
}*/
