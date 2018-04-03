//
//  ImplementLogicMgr.m
//  LabHookKit
//
//  Created by lemon4ex on 2018/3/12.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#import "ImplementLogicMgr.h"
#include "BaseImplementLogic.h"
namespace LabHookKit {
    
    ImplementLogicMgr *ImplementLogicMgr::_sharedInstance = NULL;
    ImplementLogicMgr *ImplementLogicMgr::sharedMgr()
    {
        if (!_sharedInstance) {
            _sharedInstance = new ImplementLogicMgr();
        }
        return _sharedInstance;
    }
    
    void ImplementLogicMgr::registerImplementLogic(BaseImplementLogic *logic){
        logic->allocateClass();
        logic->initImplement();
        logic->registerClass();
        _logicMap.insert(std::pair<std::string, BaseImplementLogic *>(logic->getClassName(),logic));
    }
    
    BaseImplementLogic *ImplementLogicMgr::getImplementLogic(Class _class)
    {
        return getImplementLogic(object_getClassName(_class));
    }
    
    BaseImplementLogic *ImplementLogicMgr::getImplementLogic(const std::string &className)
    {
        std::map<std::string, BaseImplementLogic *>::iterator iter = _logicMap.find(className);
        if (iter == _logicMap.end()) {
            return nullptr;
        }
        else
        {
            return iter->second;
        }
    }
    
}
