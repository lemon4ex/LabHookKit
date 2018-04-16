# LabHookKit

一个用于快速Hook的工具库，可以方便的将OC代码使用C++代码进行重包装。用于使用C++完成Hook逻辑和动态生成OC类实现。

----

# 背景
为了避免OC代码被简单的逆向，增加逆向工程难度，故使用C++代码来包装OC实现逻辑。

使用C++代码后，配合几维安全编译器的混淆功能，能够完全将类隐藏，class-dump无法导出任何想要隐藏的类的头文件。

使用C++代码包装后，所有新增类的类名、方法名以及被Hook的类的方法名都使用的是C++字符串，几维编译后所有字符串都会被加密。

# 编译环境：

* XCode7.2+
* 需要C++11支持

# 工程结构
```
├── LabHookKit
│   ├── BaseHookLogic.h
│   ├── BaseHookLogic.mm // Hook逻辑基类，用于生成子类
│   ├── BaseImplementLogic.h
│   ├── BaseImplementLogic.mm // 类实现逻辑基类，用于生成子类
│   ├── HookLogicMgr.h
│   ├── HookLogicMgr.mm // Hook逻辑管理器
│   ├── ImplementLogicMgr.h 
│   ├── ImplementLogicMgr.mm // 实现逻辑管理器
│   ├── Info.plist
│   ├── LabHookKit.h // 类库导出的头文件
│   └── Macro.h // 宏工具，可帮助快速使用此工具库，建议查看
├── LabHookKit.xcodeproj
│   ├── project.pbxproj
│   ├── project.xcworkspace
│   └── xcuserdata
└── README.md  // 说明文件
```

# 使用示例

## Hook某个类，使用C++类包装实现新的逻辑
头文件
```
#ifndef TypingControllerHookLogic_h
#define TypingControllerHookLogic_h

#import <Foundation/Foundation.h>
#include <LabHookKit/LabHookKit.h>

// 继承至 BaseHookLogic，实现自己的逻辑
class TypingControllerHookLogic : public LabHookKit::BaseHookLogic {
    
public:
    // 声明消息映射，具体原理可以看宏的实现
    DECLARE_HOOK_MESSAGE_MAP(TypingControllerHookLogic, TypingController)
    
    // 声明需要替换的Hook类消息的实现
    DECLARE_HOOK_MESSAGE(void, trySendTyping,int type);
};

#endif
```
实现文件
```
#include "TypingControllerHookLogic.h"
#include "TCCSetting.h"

using namespace LabHookKit;

// 开始消息映射，所有添加消息，Hook消息需要写在BEGIN_HOOK_MESSAGE_MAP和END_HOOK_MESSAGE_MAP之间，所有宏都有XXXXXXXXX_V2版本,更加易用。
BEGIN_HOOK_MESSAGE_MAP(TypingControllerHookLogic)
HOOK_INSTANCE_MESSAGE(TypingControllerHookLogic, trySendTyping:, trySendTyping)
END_HOOK_MESSAGE_MAP(TypingControllerHookLogic)

// OC新方法的实现
DEFINITION_HOOK_MESSAGE(TypingControllerHookLogic, void, trySendTyping,int type)
{
    TypingController *self = (__bridge TypingController *)this;
    TCCSetting *setting = TCCSetting::sharedSetting();
    if (setting->disableSendTyping) {
        
    }
    else {
        TypingControllerHookLogic *logic = dynamic_cast<TypingControllerHookLogic *>(HookLogicMgr::sharedMgr()->getHookLogic(self));
        if (logic) {
            ClassHookInfo *info = logic->getClassHookInfo(sel);
            if (info) {
              info->originImp(self, sel,type);
            }
        }
    }
}
```

使用快速宏帮助开发
```
#ifndef GameControllerHookLogic_h
#define GameControllerHookLogic_h

#import <Foundation/Foundation.h>
#include <LabHookKit/LabHookKit.h>

class GameControllerHookLogic : public LabHookKit::BaseHookLogic {
    
public:
    DECLARE_HOOK_MESSAGE_MAP_V2(GameController)
    
    DECLARE_HOOK_MESSAGE_V2(void, setGameContentForMsgWrap, CMessageWrap *wrap);
};


#endif /* GameControllerHookLogic_h */
```

```
#include "GameControllerHookLogic.h"

// 推荐使用XXXXXXXXX_V2版本,更直观和易用。
BEGIN_HOOK_MESSAGE_MAP_V2(GameController)
HOOK_INSTANCE_MESSAGE_V2(GameController, SetGameContentForMsgWrap, setGameContentForMsgWrap)
END_HOOK_MESSAGE_MAP_V2(GameController)

DEFINITION_HOOK_MESSAGE_V2(GameController, void, setGameContentForMsgWrap,CMessageWrap *wrap)
{
    DECLARE_SELF_V2(GameController);
    [self sendGameMessage:nil toUsr:nil];
    
    // 声明原返回类型
    DECLARE_ORIGIN_MESSAGE_V2(GameController, void, CMessageWrap *wrap);
    // 调用原来的方法
    return ORIGIN_MESSAGE_V2(GameController, wrap);
}
```
## 动态增加一个OC类，使用C++类包装实现新类的的所有逻辑
头文件
```
#ifndef TCCChatSiderbarCellLogic_h
#define TCCChatSiderbarCellLogic_h

#import <Foundation/Foundation.h>
#include <LabHookKit/LabHookKit.h>

// 声明OC类，提供头文件，以便后续直接调用OC方法，只有头文件，无实现文件，因为类是动态生成
@interface TCCChatSiderbarCell : UITableViewCell
//@property (nonatomic, strong) MMHeadImageView *headView;
//@property (nonatomic, strong) MMBadgeView *unreadCountView;
- (void)updateCellWithSessionInfo:(MMSessionInfo *)sessionInfo contact:(CContact *)currentContact backgroundImage:(BOOL)backgroundImage;
@end

class TCCChatSiderbarCellLogic : public LabHookKit::BaseImplementLogic {
    
public:    
    DECLARE_IMPLEMENT_MESSAGE_MAP(TCCChatSiderbarCellLogic, UITableViewCell, TCCChatSiderbarCell)
    
//    virtual void initImplement();
    
    // OC类的方法实现声明
    id initWithStyle(SEL sel, UITableViewCellStyle style, NSString *reuseIdentifier);
    void layoutSubviews(SEL sel);
    void updateCell(SEL sel, MMSessionInfo *sessionInfo, CContact *currentContact,BOOL backgroundImage);
};

#endif
```

实现文件
```
#include "TCCChatSiderbarCellLogic.h"

using namespace LabHookKit;

static const char kHeadViewKey = '\0';
static const char kUnreadCountViewKey = '\0';

// 初始化新类的实现逻辑
void TCCChatSiderbarCellLogic::initImplement(){
    addInstanceMethod("initWithStyle:reuseIdentifier:",(LabHookKit::IMPMagicFuncPtr)&TCCChatSiderbarCellLogic::initWithStyle,"v@:i@");
    addInstanceMethod("layoutSubviews",(LabHookKit::IMPMagicFuncPtr)&TCCChatSiderbarCellLogic::layoutSubviews,"v@:");
    addInstanceMethod("updateCellWithSessionInfo:contact:backgroundImage:",(LabHookKit::IMPMagicFuncPtr)&TCCChatSiderbarCellLogic::updateCell,"v@:@@B");
}

id TCCChatSiderbarCellLogic::initWithStyle(SEL sel, UITableViewCellStyle style, NSString *reuseIdentifier)
{
//    TCCChatSiderbarCell *self = (__bridge TCCChatSiderbarCell *)this;
//    struct objc_super superClass = {self,self.superclass};
//    self = ((id(*)(struct objc_super *,SEL,...))objc_msgSendSuper)(&superClass, sel, style, reuseIdentifier);

    // 定义self变量，将this指针强制转换为OC对象指针
    DECLARE_SELF_V2(TCCChatSiderbarCell)
    // 声明父类方法的类型
    DECLARE_SUPER_MESSAGE_V2(TCCChatSiderbarCell, id, UITableViewCellStyle style, NSString *reuseIdentifier);
    // 调用父类方法
    self = SUPER_MESSAGE_V2(TCCChatSiderbarCell, style, reuseIdentifier);
    if(self) {
        MMHeadImageView *headView = (MMHeadImageView*)[objc_getClass("MMHeadImageHelper") getMainFrameHeadImageViewWithUsrName:nil headImgUrl:nil bAutoUpdate:YES bRoundCorner:YES];
        headView.headUseScene = 0;
        headView.imageSize = CGSizeMake(45, 45);
        headView.frame = CGRectMake(10, 10, 45, 45);
        [self.contentView addSubview:headView];
        objc_setAssociatedObject(self, &kHeadViewKey, headView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        
        MMBadgeView *unreadCountView = [[objc_getClass("MMBadgeView") alloc]initWithFrame:CGRectZero];
        unreadCountView.frame = CGRectMake(-5, -5, 0, 0);
        [self.contentView addSubview:unreadCountView];
        objc_setAssociatedObject(self, &kUnreadCountViewKey, unreadCountView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    return self;
}

void TCCChatSiderbarCellLogic::layoutSubviews(SEL sel)
{
    TCCChatSiderbarCell *self = (__bridge TCCChatSiderbarCell *)this;
    struct objc_super superClass = {self,self.superclass};
    ((void(*)(struct objc_super *,SEL))objc_msgSendSuper)(&superClass, sel);
    
    MMHeadImageView *headView = objc_getAssociatedObject(self, &kHeadViewKey);
    MMBadgeView *unreadCountView = objc_getAssociatedObject(self, &kUnreadCountViewKey);
    
    CGRect frame = unreadCountView.frame;
    CGRect headFrame = headView.frame;
    
    frame.origin.y = CGRectGetMinY(headFrame) - CGRectGetHeight(frame) / 2;
    frame.origin.x = CGRectGetMaxX(headFrame) + CGRectGetHeight(frame) / 2 - CGRectGetWidth(frame);
    
    unreadCountView.frame = frame;
}

void TCCChatSiderbarCellLogic::updateCell(SEL sel, MMSessionInfo *sessionInfo, CContact *currentContact,BOOL backgroundImage)
{
    TCCChatSiderbarCell *self = (__bridge TCCChatSiderbarCell *)this;
    CContact *contact = sessionInfo.m_contact;
    NSUInteger unReadCount = sessionInfo.m_uUnReadCount;
    MMHeadImageView *headView = objc_getAssociatedObject(self, &kHeadViewKey);
    MMBadgeView *unreadCountView = objc_getAssociatedObject(self, &kUnreadCountViewKey);
    
    [headView updateUsrName:contact.m_nsUsrName withHeadImgUrl:contact.m_nsHeadImgUrl];
    if (unReadCount) {
        unreadCountView.hidden = NO;
        
        if ([contact.m_nsUsrName isEqualToString:@"brandsessionholder"]) {
            //  订阅号显示小圆点
            [unreadCountView setString:@""];
        }
        else if (!contact.isChatStatusNotifyOpen) {
            //  消息免打扰显示小圆点
            [unreadCountView setString:@""];
        }
        else {
            [unreadCountView setValue:unReadCount];
        }
    }
    else
    {
        unreadCountView.hidden = YES;
    }

    if ([currentContact.m_nsUsrName isEqualToString:contact.m_nsUsrName]) {
        self.backgroundView = nil;
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.backgroundColor = UIColor.clearColor;
    } else {
        UIView *view = [UIView new];
        view.backgroundColor = [UIColor colorWithWhite:1 alpha:0.5];
        self.backgroundView = backgroundImage ? view : nil;
        self.selectionStyle = UITableViewCellSelectionStyleDefault;
        self.backgroundColor = backgroundImage ? UIColor.clearColor : UIColor.whiteColor;
    }
}
```
