#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "GamePot.h"
#import "GamePotHttpClient.h"
#import "GamePotHandler.h"
#import "GamePotLog.h"
#import "GamePotGraphQLRequest.h"
#import "GamePotSharedPref.h"
#import "GamePotUtil.h"
#import "GamePotChat.h"
#import "SystemServices.h"
#import "GamePotError.h"
#import "GamePotPurchaseInfo.h"
#import "GamePotWebView.h"
#import "GamePotAgreeView.h"
#import "UIView+Toast.h"
#import "GamePotVoidedView.h"
#import "GamePotNotificationServiceExtension.h"
//#import "GamePotLocaleManager.h"

#define GAMEPOT_VERSION @"3.5.3"

//! Project version number for Common.
FOUNDATION_EXPORT double GamePotVersionNumber;

//! Project version string for Common.
FOUNDATION_EXPORT const unsigned char GamePotVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <Common/PublicHeader.h>

//#define SHARED_KEY_LINKING_ID @"GamePotLinkingId"
#define SHARED_KEY_GUEST_ID @"GamePotGuestId"
#define SHARED_KEY_GUEST_PASSWORD @"GamePotGuestPassword"
#define SHARED_KEY_LAST_LOGIN_TYPE @"GamePotLastLoginType"
#define SHARED_KEY_LICENSE_CACHE @"GamePotLicenseCache"
#define SHARED_KEY_SOCKET_CACHE @"GamePotSocketCache"
#define SHARED_KEY_DASH_CACHE @"GamePotDashCache"
#define SHARED_KEY_DASH_API_CACHE @"GamePotDashAPICache"
#define SHARED_KEY_CHECK_ONEDAY @"GamePotCheckOneDay"
#define SHARED_KEY_AGREE_CHECKED @"GamePotAgreeChecked"
#define SHARED_KEY_GDPR_CHECKED_INFO @"GamePotGDPRCheckedInfo"


@protocol GamePotPurchaseDelegate<NSObject>
@required
- (void) GamePotPurchaseSuccess:(GamePotPurchaseInfo*)_info;
- (void) GamePotPurchaseFail:(NSError*)_error;
- (void) GamePotPurchaseCancel;
@end

@interface GamePot : NSObject

@property (nonatomic) id purchaseDelegate;

@property (nonatomic) GamePotAgreeOption* agreeBuilder;
@property (nonatomic) BOOL autoAgree;


+ (GamePot*) getInstance;

- (void) changeProjectId:(NSString *) _id;
- (void) setup;

- (void) setupWithAppStatus:(GamePotAppStatusNeedUpdateHandler)_update
             setMaintenance:(GamePotAppStatusMaintenanceHandler)_maintenance;

- (NSArray*) getConfigs;
- (NSString*) getConfig:(NSString*)_key;

- (NSString*) getMemberId;
- (NSString*) getToken;

- (NSArray*) getPurchaseItems;

- (NSString*) getPurchaseItemsJsonString;

- (void) setLanguage:(NSString*)_language;

//! 결제
- (void) purchase:(NSString*)_productId;

//! unique id 포함한 결제
- (void) purchase:(NSString*)_productId uniqueId:(NSString*)_uniqueId;

- (void) purchase:(NSString*)_productId uniqueId:(NSString*)_uniqueId serverId:(NSString*)_serverId playerId:(NSString*)_playerId etc:(NSString*)_etc;

- (void) sendPurchaseByThirdPartySDK:(NSString*)_productId
                       transactionId:(NSString*)_transactionId
                            currency:(NSString*)_currency
                               price:(NSDecimalNumber*)_price
                           paymentId:(NSString*)_paymentId
                            uniqueId:(NSString*)_uniqueId
                             storeId:(NSString*)_storeId
                             success:(GamePotCommonSuccess)_success
                                fail:(GamePotCommonFail)_fail;

- (NSArray*) getDetails;
- (NSString*) getLocalizePrice:(NSString*)_productId;
- (void) coupon:(NSString*)_couponNumber handler:(GamePotCouponHandler)_handler;
- (void) coupon:(NSString*)_couponNumber userData:(NSString*)_userData handler:(GamePotCouponHandler)_handler;

//! Push 상태 설정
- (void) setPushEnable:(BOOL)_pushEnable success:(GamePotCommonSuccess)_success fail:(GamePotCommonFail)_fail;

//! 야간 Push 상태 설정
- (void) setNightPushEnable:(BOOL)_pushEnable success:(GamePotCommonSuccess)_success fail:(GamePotCommonFail)_fail;

//! 광고 Push 상태 설정
- (void) setAdPushEnable:(BOOL)_pushEnable success:(GamePotCommonSuccess)_success fail:(GamePotCommonFail)_fail;

- (void) setPushStatus:(BOOL)_pushEnable
                 night:(BOOL)_nightPushEnable
                    ad:(BOOL)_adPushEnable
               success:(GamePotCommonSuccess)_success
                  fail:(GamePotCommonFail)_fail;

//! Push 상태
- (BOOL) getPushEnable;

//! 야간 Push 상태
- (BOOL) getNightPushEnable;

//! 광고 Push 상태
- (BOOL) getAdPushEnable;

//! 전체 Push 상태를 NSDictionary 타입으로 리턴
- (NSDictionary*) getPushStatus;

//! 전체 Push 상태를 JsonString 타입으로 리턴
- (NSString*) getPushStatusJsonString;

- (void)openAppStore;

- (void) checkAppStatus:(GamePotCommonSuccess)_success
         setFailHandler:(GamePotCommonFail)_fail
       setUpdateHandler:(GamePotAppStatusNeedUpdateHandler)_updateHandler
  setMaintenanceHandler:(GamePotAppStatusMaintenanceHandler)_maintenanceHandler;

- (void) showAppStatusPopup:(UIViewController*)_viewController
               setAppStatus:(GamePotAppStatus*)_appStatus
            setCloseHandler:(GamePotAppStatusCloseHandler)_closeHandler
             setNextHandler:(GamePotAppStatusNextHandler)_nextHandler;

- (void) showAppStatusPopup:(UIViewController*)_viewController
               setAppStatus:(GamePotAppStatus*)_appStatus
            setCloseHandler:(GamePotAppStatusCloseHandler)_closeHandler;

- (int) sendLocalPush:(NSString*)_title setMessage:(NSString*)_message setDateString:(NSString*)_date;

- (void) cancelLocalPush:(int)_id;

- (void)showNoticeWebView:(UIViewController*)_viewController;

- (void)showNotice:(UIViewController*)_viewController
  setSchemeHandler:(GamePotSchemeHandler)_schemeHandler;

- (void)showNotice:(UIViewController *)_viewController
  setSchemeHandler:(GamePotSchemeHandler)_schemeHandler
    setExitHandler:(ExitNoticeCompeltionHandler)_exitHandler;

- (void)showNotice:(UIViewController*)_viewController
setShowTodayButton:(BOOL)_showTodayButton
  setSchemeHandler:(GamePotSchemeHandler)_schemeHandler
    setExitHandler:(ExitNoticeCompeltionHandler)_exitHandler;


- (void)showEvent:(UIViewController*)_viewController
          setType:(NSString*)_type
  setSchemeHandler:(GamePotSchemeHandler)_schemeHandler
    setExitHandler:(ExitNoticeCompeltionHandler)_exitHandler;


- (void)showHelpWebView:(UIViewController*)_viewController;
- (void)showWebView:(UIViewController*)_viewController setType:(WEBVIEW_TYPE)_type setURL:(NSString*)_url;
- (void)setWebViewExitHandler:(ExitWebviewCompletionHandler)_handler;
- (void)showFAQWebView:(UIViewController*)_viewController;

- (void)showTerms:(UIViewController*)_viewController;
- (void)showPrivacy:(UIViewController*)_viewController;
- (void)showRefund:(UIViewController*)_viewController;

- (void)showAgreeView:(UIViewController*)_viewController option:(GamePotAgreeOption*)_option handler:(GamePotAgreeHandler)_handler;
- (void)showAgreeViewWithString:(UIViewController*)_viewController option:(NSString*)_option handler:(GamePotAgreeHandler)_handler;

- (NSString*) getPushToken;
- (NSString*) getFCMToken;

- (void) handleRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

- (BOOL) isReady;

- (NSString*) getChannelToken;
- (NSString*) getChannel;
- (NSString*) getChannelId;
- (NSString*) getCountry;
- (NSString*) getRemoteIP;
- (NSDictionary*) getUserData;
- (void) setDisableBilling:(BOOL)_billingDisable;
- (NSArray*) getGDPRCheckedList;
- (NSString*) getGDPRCheckedListJsonString;

- (void) safetyToast:(UIViewController*)_viewController message:(NSString*)_message;

- (void) getPurchaseDetailListAsync:(GamePotPurchaseItemHandler)_handler;
- (void) getPurchaseDetailListAsyncToJSON:(GamePotPurchaseItemToJSONHandler)_handler;

- (void) setVoidOption:(GamePotVoidedOption*)_option;
- (void) setVoidOptionWithString:(NSString*)_option;
- (void) showVoidViewDebug:(UIViewController*)_viewController;
- (NSString*) getProjectId;

- (NSDictionary*) getGDPRInfo;

- (void) sendAgreeEmail:(NSString*)_email handler:(GamePotAgreeEmailHandler)_handler;

- (void) checkAgreeEmail:(NSString*)_email
              confirmKey:(NSString*)_key
                 handler:(GamePotAgreeEmailHandler)_handler;

- (void) setAgreeInfo:(GamePotAgreeInfo*)_info handler:(GamePotAgreeStartHandler)_handler;
- (void) setUserData:(NSDictionary*)_userData handler:(GamePotUserDataHandler)_handler;


//! 사용하지 말것
- (void) doDeleteMember:(GamePotInnerHandler)_handler;
- (void) doCreateLinking:(NSString*)_userName
                password:(NSString*)_password
                provider:(NSString*)_provider
                   email:(NSString*)_email
                 handler:(GamePotInnerHandler)_handler;

- (void) doSignOut:(GamePotInnerHandler)_handler;
- (void) doLinkingByUser:(NSString*)_userName provider:(NSString*)_provider token:(NSString*)_token email:(NSString*)_email handler:(GamePotInnerHandler)_handler;
- (void) doPlugInByUser:(NSString*)_userName provider:(NSString*)_provider token:(NSString*)_token email:(NSString*)_email handler:(GamePotInnerHandler)_handler;
- (void) doDeleteLinking:(NSString*)_provider setHandler:(GamePotInnerHandler)_handler;
- (void) doGuest:(GamePotInnerHandler)_handler;
- (BOOL) doLinked:(NSString*)_providerType;
- (void) startOperation:(NSOperation*)_operation;

- (void) doLoginByThirdPartySDK:(NSString*)_userId
                       provider:(NSString*)_provider
                        handler:(GamePotInnerHandler)_handler;


- (void) setupWithSetProject:(NSString*)_projectId setLincens:(NSString*)_licensURL;
- (void) setBeta:(BOOL)_betaEnable;
- (void) setUIViewControllerForGDPR:(UIViewController*)_viewController;
- (void) setUIViewController:(UIViewController*)_viewController;
- (NSString*) getPlugInURL;
- (Boolean) isPlugInMemberMigration;
@end
