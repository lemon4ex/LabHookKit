//
//  HookLogiMgr.cpp
//  TaiChi
//
//  Created by lemon4ex on 2018/3/8.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#include "HookLogicMgr.h"
#include "BaseHookLogic.h"

namespace LabHookKit {
    
    HookLogicMgr *HookLogicMgr::_sharedInstance = NULL;
    HookLogicMgr *HookLogicMgr::sharedMgr()
    {
        if (!_sharedInstance) {
            _sharedInstance = new HookLogicMgr();
        }
        return _sharedInstance;
    }
    
    void HookLogicMgr::registerHookLogic(BaseHookLogic *logic){
        logic->initHook();
        _logicMap.insert(std::pair<std::string, BaseHookLogic *>(logic->getClassName(),logic));
    }
    
    BaseHookLogic *HookLogicMgr::getHookLogic(Class _class)
    {
        return getHookLogic(object_getClassName(_class));
    }
    
    BaseHookLogic *HookLogicMgr::getHookLogic(const std::string &className)
    {
        std::map<std::string, BaseHookLogic *>::iterator iter = _logicMap.find(className);
        if (iter == _logicMap.end()) {
            return nullptr;
        }
        else
        {
            return iter->second;
        }
    }

}