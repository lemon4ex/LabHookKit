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
    
//    template <typename T>
    BaseHookLogic *HookLogicMgr::getHookLogic(id self)
    {
        std::string name = object_getClassName(self);
        // 解决KVO时，系统创建的临时子类导致类名变化的问题
        std::string::size_type idx = name.find("NSKVONotifying_");
        if (idx == 0) {
            name = name.substr(idx + strlen("NSKVONotifying_"));
        }
        return getHookLogic(name);
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
