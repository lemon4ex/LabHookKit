//
//  ImplementLogicMgr.h
//  LabHookKit
//
//  Created by lemon4ex on 2018/3/12.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#ifndef ImplementLogicMgr_h
#define ImplementLogicMgr_h

#include <map>
#include <string>
#include <objc/runtime.h>

namespace LabHookKit {
    
    class BaseImplementLogic;
    class ImplementLogicMgr {
        std::map<std::string,BaseImplementLogic *> _logicMap;
    private:
        ImplementLogicMgr(){};
        
    public:
        static ImplementLogicMgr *_sharedInstance;
        static ImplementLogicMgr *sharedMgr();
        
        void registerImplementLogic(BaseImplementLogic *logic);
        BaseImplementLogic *getImplementLogic(const std::string &className);
        BaseImplementLogic *getImplementLogic(Class _class);
    };
}
#endif


