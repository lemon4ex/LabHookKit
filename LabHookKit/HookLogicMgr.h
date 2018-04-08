//
//  HookLogiMgr.hpp
//  TaiChi
//
//  Created by lemon4ex on 2018/3/8.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#ifndef HookLogicMgr_hpp
#define HookLogicMgr_hpp

#include <stdio.h>
#include <map>
#include <string>

namespace LabHookKit {
    
    class BaseHookLogic;
    class HookLogicMgr {
        std::map<std::string,BaseHookLogic *> _logicMap;
    private:
        HookLogicMgr(){};
        
    public:
        static HookLogicMgr *_sharedInstance;
        static HookLogicMgr *sharedMgr();
        
        void registerHookLogic(BaseHookLogic *logic);
        BaseHookLogic *getHookLogic(const std::string &className);
        BaseHookLogic *getHookLogic(id self);
    };
}

#endif /* HookLogiMgr_hpp */
