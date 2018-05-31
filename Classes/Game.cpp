//
//  Game.cpp
//  sanxiao
//
//  Created by admin on 18/5/24.
//
//

#include "Game.hpp"
Scene* Game::createScene()
{
    auto scene = Scene::create();
    auto layer = Game::create();
    scene->addChild(layer);
    return scene;
}
bool Game::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto virableSize = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("bground1.png");
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(0, 0));
    
    auto bg1 = Sprite::create("bground1.png");
    bg1->setAnchorPoint(Vec2(0, 0));
    bg1->setPosition(Vec2(0, 0));
    this->addChild(bg);
    auto qipan = Sprite::create("caijian1.png");
    qipan->setAnchorPoint(Vec2(0, 0));
    qipan->setPosition(Vec2(0, 100));
    
    this->addChild(qipan);
    
    ClippingNode* clippingNode = ClippingNode::create();
    this->addChild(clippingNode,102);
    
    
    clippingNode->setAlphaThreshold(0.05f); //设置alpha闸值
    clippingNode->setInverted(true);     //把周围的给裁剪了
    clippingNode->setStencil(qipan);   //设置模板stencil
    clippingNode->addChild(bg1, 1);
    
//    Baoshi * jihe[8][8];
    for (int i = 0; i<8; i++)
    {
        for (int j = 0; j<8; j++)
        {
            jihe[i][j] = (Baoshi*)Baoshi::create(i, j);
            jihe[i][j]->setAnchorPoint(Vec2(0, 0));
            jihe[i][j]->setPosition(Vec2(i*40, 100+j*40));
            this->addChild(jihe[i][j],6);
//            auto kuang = Sprite::create("kuang1.png");
//            kuang->setAnchorPoint(Vec2(0, 0));
//            kuang->setPosition(Vec2(i*40, 100+j*40));
//            this->addChild(kuang,7);
        }
    }
    fun_shanchu();
    zhuangtai = false;
    kuang = Sprite::create("kuang1.png");
    kuang->setAnchorPoint(Vec2(0, 0));
    kuang->setVisible(false);
    kuang->setPosition(Vec2(0, 100));
    this->addChild(kuang,8);

    score = Label::createWithSystemFont("score:0000","Marker Felt.ttf",30);
    score->setColor(Color3B::YELLOW);
    score->setAnchorPoint(Vec2(0,1));
    score->setPosition(Vec2(0,virableSize.height));
    bg1->addChild(score);
    sc = 0;
    return true;
}
bool Game:: jiancha()
{
    xiugai = false;
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            int ceshi = 0;
            if (i-1>=0&&(jihe[i][j]->gettype()==jihe[i-1][j]->gettype()&&!shanchu.contains(jihe[i][j]))){
                if (i-2>=0&&(jihe[i][j]->gettype()==jihe[i-2][j]->gettype())){
                    xiugai = true;
                    for (int k = i-3; k>=0; k--){
                        if (jihe[k][j]->gettype()!=jihe[i][j]->gettype()){
                            break;
                        }
                        shanchu.pushBack(jihe[k][j]);
                    }
                    ceshi = 1;
                    shanchu.pushBack(jihe[i][j]);
                    shanchu.pushBack(jihe[i-1][j]);
                    shanchu.pushBack(jihe[i-2][j]);
                }
            }
            if (i+1<8&&(jihe[i][j]->gettype()==jihe[i+1][j]->gettype()&&!shanchu.contains(jihe[i][j]))){
                if (i+2<8&&(jihe[i][j]->gettype()==jihe[i+2][j]->gettype())){
                    xiugai = true;
                    for (int k = i+3; k<8; k++){
                        if (jihe[k][j]->gettype()!=jihe[i][j]->gettype()){
                            break;
                        }
                        shanchu.pushBack(jihe[k][j]);
                    }
                    if (ceshi == 0){
                        shanchu.pushBack(jihe[i][j]);
                    }
                    shanchu.pushBack(jihe[i+1][j]);
                    shanchu.pushBack(jihe[i+2][j]);
                }
            }
            if (j+1<8&&(jihe[i][j]->gettype()==jihe[i][j+1]->gettype()&&!shanchu.contains(jihe[i][j]))){
                if (j+2<8&&(jihe[i][j]->gettype()==jihe[i][j+2]->gettype())){
                    xiugai = true;
                    for (int k = j+3; k<8; k++){
                        if (jihe[i][k]->gettype()!=jihe[i][j]->gettype()){
                            break;
                        }
                        shanchu.pushBack(jihe[i][k]);
                    }
                    if (ceshi == 0){
                        shanchu.pushBack(jihe[i][j]);
                    }
                    shanchu.pushBack(jihe[i][j+1]);
                    shanchu.pushBack(jihe[i][j+2]);
                }
            }
            if (j-1>=0&&(jihe[i][j]->gettype()==jihe[i][j-1]->gettype()&&!shanchu.contains(jihe[i][j]))){
                if (j-2>=0&&(jihe[i][j]->gettype()==jihe[i][j-2]->gettype())){
                    xiugai = true;
                    for (int k = j-3; k>=0; k--){
                        if (jihe[i][k]->gettype()!=jihe[i][j]->gettype()){
                            break;
                        }
                        shanchu.pushBack(jihe[i][k]);
                    }
                    ceshi = 1;
                    shanchu.pushBack(jihe[i][j]);
                    shanchu.pushBack(jihe[i][j-1]);
                    shanchu.pushBack(jihe[i][j-2]);
                }
            }
        }
    }
    return xiugai;
}
void Game::fun_shanchu()
{
    jiancha();
    if (xiugai==true){
        int temp = 0;
        for (auto dd :shanchu){
            temp++;
            auto act1 = ScaleBy::create(1, 1.2);
            auto act2 = CallFunc::create([=](){
                 jihe[dd->getX()][dd->getY()]=nullptr;
                 dd->removeFromParentAndCleanup(true);
                sc+=30;
                string s1 = StringUtils::format("score:%4d",sc);
                score->setString(s1);
            });
            Sequence * seq;
            if (temp==shanchu.size()){
                auto act3 = CallFunc::create([=](){
                     buchong();
                });
                seq = Sequence::create(act1,act2,act3, NULL);
            }
            else{
                seq = Sequence::create(act1,act2, NULL);
            }
            dd->runAction(seq);
        }
        shanchu.clear();
    }
}
void Game::fun_shanchu1(){
    if (xiugai==true){
        int temp = 0;
        for (auto dd :shanchu){
            temp++;
            auto act1 = ScaleBy::create(1, 1.2);
            auto act2 = CallFunc::create([=](){
                 jihe[dd->getX()][dd->getY()]=nullptr;
                 dd->removeFromParentAndCleanup(true);
                sc+=30;
                string s1 = StringUtils::format("score:%4d",sc);
                score->setString(s1);
            });
            Sequence * seq;
            if (temp==shanchu.size()){
                auto act3 = CallFunc::create([=](){
                     buchong();
                });
                seq = Sequence::create(act1,act2,act3, NULL);
            }
            else{
                seq = Sequence::create(act1,act2, NULL);
            }
            dd->runAction(seq);
        }
        shanchu.clear();
    }
}
void Game::buchong()
{
    auto act1 = CallFunc::create([=](){
        for (int i = 0; i<8; i++){
            int temp = 0;
            for (int j = 0; j<8; j++){
                if (jihe[i][j]!=NULL){
                    tianjia.pushBack(jihe[i][j]);
                }
            }
            for (int j = 0; j<8; j++){
                if (jihe[i][j]==NULL){
                    temp++;
                    auto fangkuai = Baoshi::create(10, 10);
                    fangkuai->setAnchorPoint(Vec2(0, 0));
                    fangkuai->setPosition(Vec2(i*40, 420+40*(temp-1)));
                    this->addChild(fangkuai,6);
                    tianjia.pushBack((Baoshi*)fangkuai);
                }
            }
            for (int k = 0; k<8; k++){
                int sudu = 400;
                int lucheng = (int)(tianjia.at(k)->getPositionY())-100+k*40;
                auto act = MoveTo::create(lucheng/sudu, Vec2(i*40, 100+k*40));
                tianjia.at(k)->runAction(act);
                jihe[i][k] = tianjia.at(k);
                jihe[i][k]->setY(k);
                jihe[i][k]->setX(i);
            }
            tianjia.clear();
        }
        
    });
    auto da = DelayTime::create(0.5);
    auto act2 = CallFunc::create([=](){
        for (int i = 0; i<8; i++){
            for (int j = 0; j<8; j++){
             cout<<jihe[i][j]->getX()<<" "<<jihe[i][j]->getY()<<" "<<jihe[i][j]<<endl;
            }
        }
        if (xiugai==true){
         fun_shanchu();
        }

    });
    auto seq = Sequence::create(act1,da,act2, NULL);
    this->runAction(seq);
}


void Game::onEnter()
{
    
    Layer::onEnter();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(Game::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void Game::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    Layer::onExit();
    
}

bool Game::onTouchBegan(Touch * touch,Event * unused_event){
    if (zhuangtai == false){
        for (int i = 0; i<8; i++){
            for (int j = 0; j<8; j++){
                if (jihe[i][j]->getBoundingBox().containsPoint(touch->getLocation())){
                    kuang->setPosition(jihe[i][j]->getPosition());
                    kuang->setVisible(true);
                    zhuangtai = true;
                    jiaohuan = jihe[i][j];
                }
            }
        }
    }
    else{
        for (int i = 0; i<8; i++){
            for (int j = 0; j<8; j++){
                if (jihe[i][j]->getBoundingBox().containsPoint(touch->getLocation())){
                    int a,b,c,d;
                    a = jiaohuan->getX();
                    b = jiaohuan->getY();
                    c = jihe[i][j]->getX();
                    d = jihe[i][j]->getY();
                    kuang->setPosition(jihe[i][j]->getPosition());
                    if ((b==d&&(a-c)==1)||(b==d&&(a-c)==-1)||(a==c&&(b-d)==1)||(a==c&&(b-d)==-1)){
                        auto dian1 = jiaohuan->getPosition();
                        auto dian2 = jihe[i][j]->getPosition();
                        auto act1 = CallFunc::create([=](){
                            kuang->setVisible(false);
                            zhuangtai = false;
                            jihe[c][d]->stopAllActions();
                            jihe[a][b]->stopAllActions();
                            jihe[a][b]->setX(c);
                            jihe[a][b]->setY(d);
                            jihe[c][d]->setX(a);
                            jihe[c][d]->setY(b);
                            auto cc = jihe[a][b];
                            jihe[a][b] = jihe[c][d];
                            jihe[c][d] = cc;
                            jiancha();
                            if (xiugai){
                                auto move1 = MoveTo::create(1, dian1);
                                auto move2 = MoveTo::create(1, dian2);
                                jihe[c][d]->runAction(move2);
                                jihe[a][b]->runAction(move1);
                            }
                        });
//                        auto act = DelayTime::create(1.2);
                        auto act2 = CallFunc::create([=](){
                            fun_shanchu1();
                            if (xiugai==false){
                                auto cc = jihe[a][b];
                                jihe[a][b] = jihe[c][d];
                                jihe[c][d] = cc;
                                jihe[a][b]->setX(a);
                                jihe[a][b]->setY(b);
                                jihe[c][d]->setX(c);
                                jihe[c][d]->setY(d);
                            }
                        });
                        auto seq1 = Sequence::create(act1,act2, NULL);
                        this->runAction(seq1);
                        //                        jiaohuan = nullptr;
                    }

                }
                else{
                    zhuangtai = false;
                }
            }
        }

    }
    return true;
}
void Game::onTouchMoved(Touch * touch,Event * unused_event)
{

}
void Game::onTouchEnded(Touch * touch,Event * unused_event)
{
    
    log("touch ended\n");
}
void Game::onTouchCancelled(Touch * touch,Event * unused_event)
{
    log("touch cancelled\n");
}
