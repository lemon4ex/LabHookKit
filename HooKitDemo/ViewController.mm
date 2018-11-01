//
//  ViewController.m
//  HooKitDemo
//
//  Created by lemon4ex on 18/5/27.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#import "ViewController.h"
#import <LabHookKit/LabHookKit.h>

using namespace LabHookKit;

@interface SettingViewController : UIViewController

@end

class SettingViewControllerLogic : public LabHookKit::BaseImplementLogic
{
    DECLARE_IMPLEMENT_MESSAGE_MAP_V2(UIViewController, SettingViewController)
};

void SettingViewControllerLogic::initImplement()
{
    
}

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    button.frame = CGRectMake(100, 100, 100, 50);
    [button setTitle:@"测试" forState:UIControlStateNormal];
    [button setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [self.view addSubview:button];
    [button addTarget:self action:@selector(onButton) forControlEvents:64];
    
    ImplementLogicMgr::sharedMgr()->registerImplementLogic(new SettingViewControllerLogic());
}

- (void)onButton
{
    SettingViewController *settingVC = [[objc_getClass("SettingViewController")alloc]init];
    [self.navigationController pushViewController:settingVC animated:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
