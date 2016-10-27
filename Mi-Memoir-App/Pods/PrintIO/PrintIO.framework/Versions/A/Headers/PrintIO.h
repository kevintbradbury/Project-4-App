//
//  PrintIO.h
//  PrintIO Framework
//
//  Created by PrintIO on 12/13/13.
//  Copyright (c) 2013 PrintIO. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProductIds.h"
#import "PaymentOptions.h"
#import "PIOPublicConstants.h"
#import <UIKit/UIKit.h>
#import "PIOVersion.h"
#import "GTAnalyticsDelegate.h"

#import "PIOSideMenuButton.h"
#import "PIOVariantOption.h"
#import "PIODefaultPhotoSource.h"
#import "PIODefaultPhotoSourceItem.h"
#import "PIOPhotoSource.h"
#import "PIOPhotoSourceItem.h"
#import "PIOSessionManager.h"
#import "PIOPhotoSourceError.h"
#import "PIOPhotoSourceItemImageDownloader.h"
#import "GTAnalyticsEvent.h"
#import "GTAnalyticsScreen.h"

enum {
    PRINTIO_STAGING,
    PRINTIO_PRODUCTION,
}; DEPRECATED_ATTRIBUTE

enum {
    PRINTIO_OPTION_PRESENT_VIEW_FROM_LEFT = 1 << 0,
    PRINTIO_OPTION_PRESENT_VIEW_FROM_RIGHT = 1 << 1,
    PRINTIO_OPTION_PRESENT_VIEW_FROM_BOTTOM = 1 << 2,
    
    PRINTIO_JUMP_TO_SCREEN_SHOPPING_CART = 1 << 3,
    PRINTIO_ENABLE_BACK_BUTTON = 1 << 4
}Options;

@class PrintIO;

@protocol PrintIOUIDelegate <NSObject>

@optional

-(UIButton*)printIO:(PrintIO *)printIO photoSourceButtonWithImage:(UIImage *)image title:(NSString *)title;
-(NSString*)pathForPhotoSourceBackButtonImage:(PrintIO *)printIO;

@end

@protocol PrintIODelegate <NSObject>

@optional

-(void)PrintIOWidgetOnOpen;
-(void)PrintIOWidgetOnCloseWithData:(NSDictionary *)data;

/**
 Called after successfully placing an order.
 
 @param printIO PrintIO widget(sender).
 @param data NSDictionary containing order data.
 */
-(void)printIO:(PrintIO *)printIO didCompleteOrderWithData:(NSDictionary *)data;

@end

@interface PrintIO : NSObject

/**
 Get PrintIO singleton
 */
+(PrintIO *)sharedInstance;

/**
 PrintIO delegate
 */
@property (nonatomic, weak) id<PrintIODelegate> delegate;
@property (nonatomic, weak) id<GTAnalyticsDelegate> analyticsDelegate;
@property (nonatomic, weak) id<PrintIOUIDelegate> UIDelegate;

/**
 Init PrintIO widget. To get view controller, use '[self.printIO viewController]'
 
 @param recipeId Recipe Id provided by Gooten
 @param isInTestMode Default value is NO
 */
-(id)initWithRecipeId:(NSString *)recipeId isInTestMode:(BOOL)isInTestMode;

/**
 Init PrintIO widget with parent view controller.
 
 @param viewController Parent view controller. From this view controller, widget will open.
 @param recipeId Production recipeId provided by Gooten
 @param isInTestMode Default value is
 */
-(id)initWithViewController:(id)viewController recipeId:(NSString *)recipeId isInTestMode:(BOOL)isInTestMode;

/**
 Use to place live orders in production mode, without payment verification
 
 @param testMode Default value is NO
 */
-(void)setIsInTestMode:(BOOL)testMode;

/**
 Run SDK in staging environment
 
 @param recipeID Staging recipeID provided by Gooten
 */
-(void)useStagingModeWithRecipeID:(NSString *)recipeID;

/**
 Open widget by presenting view from bottom
 */
-(void)open;

/**
 Open widget with option
 
 @param option Set the options
 PRINTIO_OPTION_PRESENT_VIEW_FROM_LEFT,
 PRINTIO_OPTION_PRESENT_VIEW_FROM_RIGHT,
 PRINTIO_OPTION_PRESENT_VIEW_FROM_BOTTOM,
 PRINTIO_JUMP_TO_SCREEN_SHOPPING_CART
 PRINTIO_ENABLE_BACK_BUTTON
 */
-(void)openWithOption:(int)option;

/**
 Present widget from view controller with option
 
 @param option Set the options
 PRINTIO_OPTION_PRESENT_VIEW_FROM_LEFT,
 PRINTIO_OPTION_PRESENT_VIEW_FROM_RIGHT,
 PRINTIO_OPTION_PRESENT_VIEW_FROM_BOTTOM,
 PRINTIO_JUMP_TO_SCREEN_SHOPPING_CART
 PRINTIO_ENABLE_BACK_BUTTON
 */
-(void)presentFromViewController:(UIViewController *)viewController withOption:(int)option;

/**
 Close widget
 */
-(void)close:(NSInteger)flag;
-(void)closeWithCompletionHandler:(void(^)(void))completionHandler;

/**
 Returns PrintIO view controller. Set all options before calling this method
 */
-(UIViewController *)viewController;

/**
 Root controller flag. Set to YES if the PrintIO widget is the root controller of your application.
 
 @param isRootController Root controller flag.
 */
-(void)setIsRootController:(BOOL)isRootController;

-(void)setQAEnvironment:(BOOL)set;

#pragma mark - Navigation Bar

/**
 Change navigation bar color and title font color.
 
 @param color Color for title bar (navigation bar). If nil default color is used.
 @param tColor Color of fonts on title bar. If nil default color is used.
 @param lColor Background color for left navigation bar button. If nil, transparent will be used.
 @param rColor Background color for right navigation bar button. If nil, transparent will be used.
 @param iPath DEPRECATED OPTION
 */
- (void)navigationBarColor:(UIColor *)color titleColor:(UIColor *)tColor leftButtonBackgroundColor:(UIColor *)lColor rightButtonBackgroundColor:(UIColor *)rColor titleButtonIcon:(NSString *)iPath;

/**
 Set background image on Navigation Bar
 
 @param imagePath Path to image file.
 */
-(void)setNavigationBarBackground:(NSString *)imagePath;

/**
 Set navigation bar background image on 'Customize Product' screen
 
 @param imagePath Path to image file.
 */
-(void)setNavigationBarBackgroundForCustomizeProduct:(NSString *)imagePath;

/**
 Set icon for back button.
 
 @param path Path to image file.
 */
-(void)setIconForBackButton:(NSString *)iconPath;

/**
 Set back button hidden
 
 @param set Default value is NO
 */
-(void)setBackButtonHidden:(BOOL)set;

/**
 Set status bar style and visibility.
 
 @param dark Default value is NO
 @param hidden Default value is NO
 */
-(void)setStatusBarDark:(BOOL)dark hidden:(BOOL)hidden;

/**
 Set three buttons Back, Menu and Cart button in navigation bar for Featured Products screen
 
 @param set Default value is NO
 */
-(void)setThreeButtonsNavigationBarStyle:(BOOL)set;

/**
 Set colors scheme for navigation bar with "Save to" shopping cart button
 
 @param bcgColor Navigation bar background color
 @param titleColor Navigation bar title color
 @param btnBcgColor Button's background color
 @param btnTitleColor Button's title color
 */
-(void)setNavigationBarSaveToCartBackgroundColor:(UIColor *)bcgColor titleColor:(UIColor *)titleColor buttonBackgroundColor:(UIColor *)btnBcgColor buttonTitleColor:(UIColor *)btnTitleColor;

/**
 Set and show logo in navigation bar
 
 @param iconPath Path to image file
 */
-(void)setNavigationBarLogo:(NSString *)iconPath;

#pragma mark - Side Menu

/**
 Use Side Menu
 
 @param mIconPath Path to image for Menu icon. If nil, default icon will be used.
 */
-(void)useSideMenuWithMenuIcon:(NSString *)iconPath;

/**
 Set side menu items: array of options presented as PIOSideMenuButton:
 
 PIOSMButtonTypeQualityGuarantee,
 PIOSMButtonTypeAbout,
 PIOSMButtonTypeHowItWorks,
 PIOSMButtonTypePastOrders,
 PIOSMButtonTypeOrderStatus
 PIOSMButtonTypeContactUs
 PIOSMButtonTypeHelp
 
 By default all items are presented in side menu
 */
-(void)setSideMenuItems:(NSArray *)items;

/**
 Get default side menu items, which you can edit and customize
 
 @return Array of PIOSideMenuButton objects
 */
-(NSArray *)defaultSideMenuItems;

/**
 Slide side menu from right. Default value is NO.
 
 @param set Default value is NO.
 */
-(void)slideSideMenuFromRight:(BOOL)set;

/**
 Hide photo sources section in Side Menu
 
 @param set Default value is NO
 */
-(void)hidePhotoSourcesInSideMenu:(BOOL)set;

/**
 Hide version label in side menu
 
 @param set Default value is NO
 */
-(void)hideVersionInSideMenu:(BOOL)set;

/**
 Set email for "Contact Us" button
 
 @param email Customer support email
 */
-(void)setContactUsEmail:(NSString *)email;

#pragma mark - Choose Country Screen

/**
 Change title on 'Choose Country' screen
 
 @param title New title
 */
-(void)setTitleForChooseCountryScreen:(NSString *)title;

/**
 Hide search icon from navigation bar on 'Choose Country' screen
 
 @param set Default value is NO
 */
-(void)hideSearchIconInChooseCountryScreen:(BOOL)set;

/**
 Change placeholder text in search bar, and set magnifying glass vissible or hidden
 
 @param text Placeholder text
 @param set Default value is NO
 */
-(void)setPlaceholderTextForSearchBarInChooseCountryScreen:(NSString *)text hideMagnifyingGlass:(BOOL)set;

/**
 Change the color of navigation bar in 'Choose Country' screen
 
 @param color Color to set
 */
-(void)setNavigationBarBackgroundColorForChooseCountryScreen:(UIColor *)color;

#pragma mark - Products

/**
 Hide category+search view on Featured Products screen. Default value is NO;
 
 */
-(void)hideCategoriesInFeaturedProducts:(BOOL)hide;

/**
 Hide coming soon products from product's list
 
 @param hide Default value is NO
 */
-(void)hideComingSoonProducts:(BOOL)hide;

/**
 Show country selection. By default, country selection is always shown on Featured/All products
 
 @param screen Screen:
 
 PIO_SCREEN_FEATURED_PRODUCTS
 PIO_SCREEN_PRODUCT_DETAILS
 PIO_SCREEN_OPTIONS
 */
-(void)showCountrySelectionOnScreen:(PIOScreens)screen backgroundColor:(UIColor *)backgroundColor;

/**
 Change title on Featured Products screen
 
 @param title New title
 */
-(void)setTitleForFeaturedProductsScreen:(NSString *)title;

/**
 Change label's color on items in list on Featured Products screen
 
 @param lColor Text color for left label
 @param rColor Text color for right label
 */
-(void)setFeaturedProductsLeftLabelTextColor:(UIColor *)lColor rightLabelTextColor:(UIColor *)rColor;

/**
 Set background image on Featured Products screen
 
 @param imagePath Path to image file.
 */
-(void)setFeaturedProductsBackgroundImage:(NSString *)imagePath;

/**
 Change version of Products Screen. 
 
 @param version Default screen version is PIOProductsScreenV1
 
 PIOProductsScreenV1
 PIOProductsScreenV2 - available from sdk v1.6.5(25). Dynamic products list view.
 PIOProductsScreenV3 - available from sdk v1.7.1(30). Products are in list/grid view.
 
 */
-(void)setProductsScreenVersion:(PIOProductsScreenVersion)version;

/**
 Set image url for Dymanic products list view. In order to use this method, 
 PIOProductsScreenV2 needs to be enabled.
 Available from sdk v1.6.5(25)
 
 @param url Url to image file.
 */
-(void)setProductsScreenImageUrl:(NSString *)url;

/**
 Set text for What's New Dialog. If there's no text, dialog
 will be hidden.
 
 Sample text: @"- bug fixes\n- new products added\n- new feature added"
 
 @param text Text
 */
-(void)setWhatsNewDailogText:(NSString *)text;

/**
 Show bottom bar with search, like, share and rate us options
 Available from SDK v1.5.19(24)
 
 @param likeUsUrl URL to web page (facebook page etc...)
 @param rateUsAppId Application id from app store
 @param shareText Text for sharing
 */
-(void)showBottomBarWithLikeUsURL:(NSURL *)likeUsURL rateUsAppId:(NSString *)rateUsAppId shareText:(NSString *)shareText;

/**
 Set which products will be in hero, on Products page, by providing product ids.
 Max number of products is five.
 
 @param productsIds Array of product ids
 
 Example:
 NSArray *productsInHero = @[[NSNumber numberWithInt:GTProductPhoneCases], [NSNumber numberWithInt:GTProductTabletcases]];
 */
-(void)setProductsInHero:(NSArray *)productsIds;

/**
 Add image obj in hero, which will lead to url, when user taps on it
 
 @param image UIImage object
 @param url NSURL object
 */
-(void)setImageInHero:(UIImage *)image url:(NSURL *)url;

/**
 Show all products and product variants
 
 @param set Default value is NO
 */
-(void)setUseDefaultProductSettings:(BOOL)set;

#pragma mark - Product Details

/**
 Show title below navigation bar on Product Details screen
 
 @param set Default value is NO
 */
-(void)productDetailsShowTitleBelowNavBar:(BOOL)set;

/**
 Show menu button in navigation bar on Product Details screen
 
 @param set Default value is NO
 */
-(void)productDetailsShowMenuBtnInNavBar:(BOOL)set;

/**
 Provide Quality Guarantee text for Product Details screen
 
 @param text Quality Guarantee text
 */
-(void)setQualityGuaranteeText:(NSString *)text;

/**
 Set 'Starting at' and 'Retail price' titles hidden
 
 @param set Default value is NO
 */
-(void)setPriceTitleHidden:(BOOL)set;

/**
 Set available products. 
 
 @param availableProducts List of product ids, which will be shown in product's list
 
 Example:
 NSArray *availableProducts = @[[NSNumber numberWithInt:GTProductMousepads], [NSNumber numberWithInt:GTProductPhoneCases]];
 
 */
-(void)setAvailableProducts:(NSArray *)availableProducts;

/**
 Set retail discont percent for product details screen
 
 @param percent 
 */
-(void)setRetailDiscountPercent:(float)percent;

#pragma mark - Photo Sources

/**
 Set available photo sources
 
 @param photoSources Array of PIOSideMenuButton objects, represents which types of photo sources will be
 available to user. Types:
 
 PIO_SM_FACEBOOK
 PIO_SM_INSTAGRAM
 PIO_SM_GOOGLE_PHOTOS
 PIO_SM_FLICKR
 PIO_SM_DROPBOX
 PIO_SM_PHOTOBUCKET
 PIO_SM_PHONE
 PIO_SM_PASSED_PHOTOS
 */
-(void)setAvailablePhotoSources:(NSArray *)photoSources;

/**
 Set custom photo sources
 
 @param customPhotoSources Array of id<PhotoSource> objects 
 
 */
-(void)setCustomPhotoSources:(NSArray*)customPhotoSources;

/**
 When user enters 'Select Photos' screen, selected photo source will be opened by default.
 If an album id is passed in, if exist, that album will be opened.
 
 @param pSource Photo source:
 
 PIO_PS_FACEBOOK
 PIO_PS_INSTAGRAM
 PIO_PS_GOOGLE_PHOTOS
 PIO_PS_FLICKR
 PIO_PS_DROPBOX
 PIO_PS_PHOTOBUCKET
 PIO_PS_PHONE
 PIO_PS_PASSED_PHOTOS // added in v1.0.34
 PIO_PS_CUSTOM // added in v1.8.21
 
 @param albumId Album id (Currently works only for PIO_SM_PHOTOBUCKET photo source)
 
 */

-(void)setDefaultPhotoSource:(PIOPhotoSources)pSource albumId:(NSString *)albumId;

/*
 A flag that determines whether passed images are preselected on the 'Select Photos' screen.
 */

-(void)setPreselectPassedImages:(BOOL)shouldPreselectPassedImages;

/**
 Pass in images URLs or UIImage objects.
 
 @param images Array of image urls or/and UIImage objects
 */
-(void)setImages:(NSArray *)images;

/**
 If user pass in images usinig method 'images', this method can disable photo sources,
 forcing user to use only passed photos.
 
 This method overrides method 'setAvailablePhotoSources'
 */
-(void)disablePhotoSourcesWhenImagesArePassedIn:(BOOL)disable;

/**
 Disable photo sources only if image is passed in, and user selects template with
 one photo.
 */
-(void)disablePhotoSourcesForOnePhotoTemplate:(BOOL)disable;

/**
 Enables photo sources in Customize Product screen only, if they're disabled
 using methods 'disablePhotoSourcesWhenImagesArePassedIn' and 'disablePhotoSourcesForOnePhotoTemplate'
 */
-(void)enablePhotoSourcesInCustomizeProduct:(BOOL)set;

/**
 Set passed in image to be first in row for all photo sources.
 */
-(void)setPassedImageFirstInPhotoSources:(BOOL)set;

/**
 Hide icon for Upload Instructions text in Photo Sources screen. Default value is NO.
 */
-(void)hideIconForUploadInstructions:(BOOL)hide;

/**
 Set Instagram credentials. By default, PrintIO credentials are used.
 */
-(void)setInstagramClientID:(NSString *)clientId redirectUrl:(NSString *)redirectUrl;

/**
 Set access token for Instagram
 
 @param accessToken Valid access token for session
 */
-(void)setInstagramAccessToken:(NSString *)accessToken;

/**
 Set Flickr credentials. By default, PrintIO credentials are used.
 */
-(void)setFlickrKey:(NSString *)key secretKey:(NSString *)secretKey redirectUrl:(NSString *)redirectUrl;

/**
 Set Dropbox credentials. By default, PrintIO credentials are used.
 */
-(void)setDropboxKey:(NSString *)key redirectUrl:(NSString *)redirectUrl;

/**
 Set Facebook credentials. By default, PrintIO credentials are used.
 */
-(void)setFacebookAppId:(NSString *)appId redirectUrl:(NSString *)redirectUrl;

/**
 Set access token for Facebook
 
 @param aToken Valid access token for session
 */
-(void)setFacebookAccessToken:(NSString *)aToken;

/**
 Set username and password for Photobucket (autologin)
 
 @param userName Username or email for Photobucket account
 @param password Password
 */
-(void)setPhotobucketUsername:(NSString *)userName password:(NSString *)password;

/**
 Set access token for Photobucket
 
 @param aToken Valid access token for session
 @param username Username
 @param baseUrl Base url for Photobucket
 */
-(void)setPhotobucketAccessToken:(NSString *)aToken userName:(NSString *)username baseURL:(NSString *)baseUrl;

/**
 Change title for Photo Sources screen
 
 @param title New title
 */
-(void)setTitleForPhotoSourcesScreen:(NSString *)title;

/**
 Hide shopping cart icon from Photo Sources screen
 
 @param set Default value is NO
 */
-(void)hideCartInPhotoSources:(BOOL)set;

/**
 Show 'Select All' button on Photo Sources screen which selects all images in the current folder
 
 @param shouldShow Default value is YES
 */
-(void)showSelectAllButton:(BOOL)shouldShow;

#pragma mark - Customize Product

/**
 Show/hide tab bar in Customize Product screen. Default value is YES
 
 @param show Set show/hide
 @param imagePath Path to image file.
 */
-(void)showToolbarInCustomizeProduct:(BOOL)show backgroundImage:(NSString *)imagePath;

/**
 Hide list with images in customization screen
 */
-(void)hideImagesListInCustomizeProduct:(BOOL)hide;

/**
 Set photo(s) arrangement in Customize Product screen
 
 @param
 PIO_PHOTO_ARRANGEMENT_CHOOSE,
 PIO_PHOTO_ARRANGEMENT_AUTO,
 PIO_PHOTO_ARRANGEMENT_MANUAL
 
 */
-(void)setPhotoArrangement:(NSInteger)option;

/**
 Change image for "Add photos" button in Customize Product screen
 
 @param imagePath Path to image file.
 */
-(void)setIconForAddPhotosButton:(NSString *)imagePath;

/**
 Change icon for 'Save' button on Customize Product screen
 
 @param imagePath Path to image file.
 */
-(void)setIconForSaveButtonInCustomizeProduct:(NSString *)imagePath;

/**
 Set Pop up balloon in Customize Product screen
 
 @param path Path to background image.
 @param text Balloon text.
 @param textColor Text color.
 */
-(void)setPopUpWithImage:(NSString *)path text:(NSString *)text textColor:(UIColor *)textColor;

/**
 Set time of visibility for Double Tap ballon in Customize Product screen

 @param timeInSeconds Time in seconds. Set -1 if ballon should be visible all the time.
 Default time is 2 seconds.
 */
-(void)setDoubleTapBalloonVisibilityTime:(int)timeInSeconds;

/**
 Show custom dialog for helping user how to edit a photo

 @param Path to image.
 */
-(void)showHelpDialogWithImage:(NSString *)imagePath;

/**
 Set same photo on front and back side of product.
 Currently it only supports PRODUCT_THROW_PILLOWS.
 
 @param productId Product id
 */
-(void)setSamePhotoOnFrontAndBackSideOfProduct:(NSInteger)productId;

/**
 Replace default template text for productIds:
 
 NSArray *photobookText = @[@"First text", @"Second text", @"Third text"];
 NSArray *flatCardsText = @[@"Flat card first text"];
 
 NSDictionary *textDict = [NSDictionary dictionaryWithObjectsAndKeys:
                            flatCardsText, @(GTProductFlatCards),
                            photobookText, @(PRODUCT_PHOTO_BOOKS()), nil];
 
 @param texts Array of NSDictionary with text and productId
 */
-(void)setDefaultTemplateTexts:(NSDictionary *)textDict;

/**
 Filter templates to show only one photo template
 
 @param set Dafault value is NO
 */
-(void)showOnlyOnePhotoTemplates:(BOOL)set;

/**
 Set keyboard background color. Only applies to landscape keyboard.
 Available from SDK v1.5.10(23)
 
 @param color Defalut color is ligh grey.
 */
-(void)setKeyboardBackgroundColor:(UIColor *)color;

#pragma mark - Image Editor

/**
 Set which buttons will be visible in Image Editor toolbar. By default, all buttons are visible.
 
 @param buttons Array of PIOButton objects of types:
 PIO_BUTTON_IMAGE_EDITOR_INFO,
 PIO_BUTTON_IMAGE_EDITOR_ROTATE,
 PIO_BUTTON_IMAGE_EDITOR_EDIT_TEXT,
 PIO_BUTTON_IMAGE_EDITOR_EFFECTS
 */
-(void)imageEditorShowButtons:(NSArray *)buttons;

#pragma mark - Shopping Cart

/**
 Set custom icon for Shopping Cart
 
 @param path Path to image file.
 @param set Set to YES if image has red circle for number of items in cart.
 @param lPosition Position of label with number of products in cart
 @param tColor Text color of label with number of products in cart
 */
-(void)setIconForShoppingCart:(NSString *)path withNumberOfProducts:(BOOL)set labelPosition:(CGPoint)lPosition textColor:(UIColor *)tColor;

/**
 Set custom icon for Shopping Cart
 
 @param path Path to image file.
 @param set Set to YES to show number of items in cart.
 @param labelPosition Position of label with number of products in cart
 @param circleColor Color of label background (circle background)
 @param textColor Text color of label with number of products in cart
 */
-(void)setIconForShoppingCart:(NSString *)path withNumberOfProducts:(BOOL)set labelPosition:(CGPoint)labelPosition circleColor:(UIColor *)circleColor textColor:(UIColor *)textColor;

/**
 Change title for "Shopping Cart" screen
 
 @param title New title
 */
-(void)setTitleForShoppingCart:(NSString *)title;

/**
 Toggle 'Keep Shopping' button on the Shopping Cart screen.
 
 @param showsButton Button visibility flag. Default is YES.
 */
-(void)showKeepShoppingButtonInShoppingCart:(BOOL)showsAddButton;

/**
 Customize 'Keep Shopping' button
 
 @param title New title for button
 @param iconPath Path to icon file. Default is nil.
 */
-(void)setKeepShoppingButtonTitle:(NSString *)title icon:(NSString *)iconPath;

/**
 Change icon for Back button on Shopping Cart screen
 
 @param iconPath Path to icon file. Default is nil.
 */
-(void)setIconForShoppingCartBackButton:(NSString *)iconPath;

/**
 Get number of items in shopping cart
 */
+(NSInteger)numberOfItemsInShoppingCart;

/**
 Set promo code to get discount
 
 @param promoCode Promo code
 */
-(void)setPromoCode:(NSString *)promoCode;

/**
 Hides cart button from navigation bar, when cart is empty
 
 @param set Default value is NO
 */
-(void)hideCartButtonWhenCartIsEmpty:(BOOL)set;

/**
 Close widget when tap on Back button in Shopping Cart screen
 
 @param Default value is NO
 */
-(void)closeWidgetFromShoppingCart:(BOOL)set;

/**
 Delete all items(products) from Shopping cart
 */
+(void)clearShoppingCart;

/**
 Get shopping cart JSON content
 */
+(NSString *)shoppingCartJSONContent;

/**
 Set the content of shopping cart
 
 @param jsonString JSON content string
 */
+(void)setShoppingCartContent:(NSString *)jsonString;

#pragma mark - Country, Currency and Language

/**
 Set country code
 
 @param countryCode Country code
 */
-(void)setCountryCode:(NSString *)countryCode;

/**
 Set currency code
 
 @param currencyCode Currency code
 */
-(void)setCurrencyCode:(NSString *)currencyCode;

/**
 Set language code
 
 @param languageCode Language code
 */
-(void)setLanguageCode:(NSString *)languageCode;

#pragma mark - Shipping Addresses screen

/**
 Change highlight color for address selection on 'Select Address'
 screen
 
 @param color New color. Default is light green.
 */
-(void)setColorForAddressSelection:(UIColor *)color;

/**
 Remove all saved shipping addresses
 */
+(void)clearShippingAddresses;

/**
 Remove all saved billing addresses
 */
+(void)clearBillingAddresses;

#pragma mark - Order Completed screen

/**
 Change title for 'Order Completed' screen
 
 @param title New title
 */
-(void)setTitleForOrderCompletedScreen:(NSString *)title;

/**
 Change icon for company logo on 'Order Completed' screen
 
 @param iconPath File path to icon
 */
-(void)setIconForOrderCompletedScreen:(NSString *)iconPath;

/**
 Change company message below company logo on 'Order Completed' screen
 
 @param message New message
 */
-(void)setMessageForOrderCompletedScreen:(NSMutableAttributedString *)message;

/**
 Change function of 'Close' button on 'Order Completed' screen
 
 @param set Default value is NO
 */
-(void)orderCompletedScreenCloseButtonShouldPerformBack:(BOOL)set;

/**
 Set order's partner source id 
 
 @param sourceId Partner source id
 */
-(void)setPartnerSourceId:(NSString *)sourceId;

/**
 Set order's meta data
 
 @param meta Meta data (key, value)
 */
-(void)setOrderMeta:(NSDictionary *)meta;

#pragma mark - Other Customization

/**
 Import customization XML file
 
 @param xmlData Customization xml file.
 
 Example: NSString *xmlPath = [[NSBundle mainBundle] pathForResource:@"customization" ofType:@"xml"];
 NSData *xmlData = [NSData dataWithContentsOfFile:xmlPath];
 */
-(void)setCustomizationXML:(NSData *)xmlData;

/**
 Set custom fonts from main app bundle.
 
 @param fonts Array of string values that contains font name and type with the exact order (light, medium, regular, bold). Example: [@"font_light.otf", @"font_medium.otf", @"font_regular.otf", @"font_bold.otf"]. Array must have four items, and fonts can be duplicated. Array also accepts
 system (normal, bold and italic) UIFont objects.
 */
-(void)setFonts:(NSArray *)fonts;

/**
 Toggles UIActivityIndicatorView on the loading view instead of the loading gif image. Calling this method will override the gif image if it has previously been set.
 
 @param style UIActivityIndicatorView's style.
 */

-(void)setLoadingActivityIndicatorViewStyle:(UIActivityIndicatorViewStyle)style;

/**
 Changes "Loading" GIF animation image. Calling this method will override the UIActivityIndicatorViewStyle if has previously been set.
 
 @param fileName GIF image file name.
 */
-(void)setLoadingGIF:(NSString *)fileName;

/**
 Change title of loading dialog
 
 @param lText New title for loading dialog.
 */
-(void)setLoadingText:(NSString *)lText;

/**
 Change icon for Help Button

 @param imagePath Path for image file
 */
-(void)setIconForHelpButton:(NSString *)imagePath;

/**
 Change partner's logo in SDK
 
 @param fileName File name of logo image, without file type extension.
 Image file needs to be stored in main bundle.
 */
-(void)setLogoFileName:(NSString *)fileName;

/**
 Set payee name for order processing

 @param payeeName Payee name
 */
-(void)setPayeeName:(NSString *)payeeName;

/**
 Set url for Terms and Conditions
 
 @params url If not set, this option will be hidden
 */
-(void)setTermsAndConditionsURL:(NSURL *)url;

/**
 Provide text for "How It Works" screen
 
 @params text Text
 */
-(void)setHowItWorksText:(NSString *)text;

/**
 Provide text for "About" screen
 
 @param text About text
 */
-(void)setAboutText:(NSString *)text;

/**
 Provide help text for Customize Product screen
 
 @param text Help text
 */
-(void)setCustomizationHelpText:(NSString *)text;

/**
 Turn off logs
 
 @param set Default value is NO
 */
-(void)turnOffLogs:(BOOL)set;

/**
 Change background color on positive buttons (Yes, Next, Ok, Save, Buy It, Make itIt.)
 
 @param bColor Background color
 @param tColor Title color
 */
-(void)setPositiveButtonsBackgroundColor:(UIColor *)bColor titleColor:(UIColor *)tColor;

/**
 Change background color on negative buttons (No, Back, Cancel, Close...)
 
 @param bColor Background color
 @param tColor Title color
 */
-(void)setNegativeButtonsBackgroundColor:(UIColor *)bColor titleColor:(UIColor *)tColor;

#pragma mark - Fonts

/**
 Change light fonts size
 
 @param Increase/decrease font size by 'value'
 */
-(void)changeSizeOfLightFontsBy:(float)value;

/**
 Change medium fonts size
 
 @param Increase/decrease font size by 'value'
 */
-(void)changeSizeOfMediumFontsBy:(float)value;

/**
 Change regular fonts size
 
 @param Increase/decrease font size by 'value'
 */
-(void)changeSizeOfRegularFontsBy:(float)value;

/**
 Change bold fonts size
 
 @param Increase/decrease font size by 'value'
 */
-(void)changeSizeOfBoldFontsBy:(float)value;

#pragma mark - Steps

/**
 Set selection color for product customization steps
 
 @param color Selection color
 */
-(void)setSelectionColor:(UIColor *)color;

/**
 Jumps directly to product.
 
 @param productId Product identifier can be found in ProductIds.h and starts with PRODUCT_
 */
-(void)goToProductId:(int)productId;

/**
 Jumps directly to product with sku
 
 @param productId Product identifier can be found in ProductIds.h and starts with PRODUCT_
 @param sku SKU for selected product
 */
-(void)goToProductId:(int)productId withSKU:(NSString *)sku;

/**
 Change title for 'Customization Options' screen
 */
-(void)setTitleForChooseOptionsScreen:(NSString *)title;

/**
 Auto selects one photo template for selected productID
 
 @param productID productID of selected product
 */
-(void)autoSelectOnePhotoTemplateForProductID:(NSInteger)productID;

/**
 Disable auto recognition and selection of iPhone model
 
 @param set Default value is NO
 */
-(void)disableAutoRecognizePhoneModel:(BOOL)set;

/**
 Show Cancel button on Options screen
 Available from SDK version 1.5.12(23)
 
 @param set Defailt value is NO
 */
-(void)showCancelOptionsButton:(BOOL)set;

#pragma mark - Google Analytics

/**
 Set tracking id for Google Analytics. If tracking id is not provided,
 analytics are disabled.
 
 @param trackingID Tracking ID provided by Google
 */
-(void)setTrackingIDForGoogleAnalytics:(NSString *)trackingID;

#pragma mark - Push Notifications

/**
 Enable push notification in SDK
 
 @param set Default value is disabled
 */
-(void)enablePushNotifications:(BOOL)set;

/**
 Set applicationId and apiKey provided from parse.com
 
 @param appId application id
 @param apiKey rest api key
 */
+(void)setParseApplicationId:(NSString *)appId apiKey:(NSString *)apiKey;

/**
 Register device to receive push notifications
 
 @param deviceToken Device token
 */
+(void)registerDeviceToken:(NSData *)deviceToken;

/**
 Display notification pop up from bottom of screen. On tap it will dismiss notification.
 
 @param userInfo Dictionary provided from didReceiveRemoteNotification
 @param backgroundColor Background color for notification pop up
 @param textColor Text color
 */
+(void)showNotification:(NSDictionary *)userInfo backgroundColor:(UIColor *)bcgColor textColor:(UIColor *)textColor;

#pragma mark - Payment settings

/**
 Set Payment option
 
 @param paymentOptions:
 PaymentOptionPayPal
 PaymentOptionCreditCard
 PaymentOptionApplePay
 PaymentOptionAll
 */
-(void)setPaymentOptions:(PaymentOptions)paymentOptions;

#pragma mark - PayPal settings

/**
 Set PayPal's client ids. Default values are client ids from Gooten
 https://developer.paypal.com/developer/applications/create
 
 @param sClientId Client ID for sandbox mode
 @param pClientId Client ID for production mode
 */
-(void)setPayPalStagingClientId:(NSString *)sClientId productionClientId:(NSString *)pClientId;

#pragma mark - Braintree settings

/**
 Set Braintree encryption keys. By default, keys from Gooten will be used
 https://www.braintreepayments.com/create-merchant
 
 For encryption key use CSE Key from API keys you get
 
 @param sEncKey Encryption(CSE) key for staging mode
 @param pEncKey Encryption(CSE) key for production mode
 */
-(void)setBraintreeStagingEncryptionKey:(NSString *)sEncKey productionEncryptionKey:(NSString *)pEncKey;

#pragma mark - ApplePay settings

/**
 Set ApplePay merchant identifier
 
 @param merchantIdentifier Merchant Identifier
 */
-(void)setApplePayMerchantIdentifier:(NSString *)merchantIdentifier;

#pragma mark - App side

/**
 Default value is NO
 */
-(void)setAppMode:(BOOL)set;

/**
 Get sdk version 
 */
-(void)getVersion:(void(^)(PIOVersion *version))success;

/**
 Use this for app mode
 */
-(void)appDidFinishLaunching;

#pragma mark - DEPRECATED

-(void)setFeaturedProductsDefaultView:(PIOFeatureProductsView)viewType DEPRECATED_ATTRIBUTE;
-(void)setPassedImageAsThumbForOnePhotoTemplate:(BOOL)set DEPRECATED_ATTRIBUTE;
-(void)removeLogoFromPaymentScreen:(BOOL)remove DEPRECATED_ATTRIBUTE;
-(void)useSinglePageCustomization:(BOOL)set DEPRECATED_ATTRIBUTE;
-(void)hideEditButtonInShoppingCart:(BOOL)set DEPRECATED_ATTRIBUTE;

/**
 TYPO - use 'setThreeButtonsNavigationBarStyle'
 */
-(void)setThreeButtonsNavigationBarSytle:(BOOL)set DEPRECATED_ATTRIBUTE;

/**
 METHOD IS DEPRECATED FROM v1.6.6(27)
 use 'showKeepShoppingButtonInShoppingCart'
 */
-(void)setShowsAddMoreProductsInShoppingCart:(BOOL)showsAddButton DEPRECATED_ATTRIBUTE;

/**
 METHOD IS DEPRECATED FROM v1.6.6(27)
 use 'setKeepShoppingButtonTitle'
 */
-(void)customizeAddMoreProductButton:(NSString *)title icon:(NSString *)iconPath DEPRECATED_ATTRIBUTE;

/**
 METHOD IS DEPRECATED FROM v1.6.3(26)
 use 'showBottomBarWithLikeUsURL'
 */
-(void)setLikeUsOnFacebookUrl:(NSString *)urlS DEPRECATED_ATTRIBUTE;
/**
 METHOD IS DEPRECATED FROM v1.6.3(26)
 use 'showBottomBarWithLikeUsURL'
 */
-(void)setAppIDFromAppleStore:(NSString *)appID DEPRECATED_ATTRIBUTE;
/**
 METHOD IS DEPRECATED FROM v1.6.1(26)
 use 'useSideMenuWithMenuIcon'
 */
-(void)useSideMenuWithMenuIcon:(NSString *)mIconPath background:(UIColor *)bcgColor DEPRECATED_ATTRIBUTE;
/**
 METHOD IS DEPRECATED FROM v1.6.1(26)
 use 'setSideMenuItems'
 */
-(void)sideMenuAddButtons:(NSArray *)buttons options:(NSArray *)options optionsTitle:(NSString *)optionsTitle optionsTitleColor:(UIColor *)oTitleColor optionsColor:(UIColor *)optionsColor accountsTitle:(NSString *)accountsTitle accountsTitleColor:(UIColor *)aTitleColor accountsColor:(UIColor *)accountsColor info:(NSArray *)info infoTitle:(NSString *)infoTitle infoTitleColor:(UIColor *)iTitleColor infoColor:(UIColor *)infoColor backgroundImageForButtons:(NSString *)path DEPRECATED_ATTRIBUTE;

/**
 METHOD IS DEPRECATED FROM v1.8.5(34)
 use 'initWithRecipeId:(NSString *)recipeId;'
 */
-(id)initWithEnvironment:(int)type productionRecipeId:(NSString *)pRecipeId stagingRecipeId:(NSString *)sRecipeId DEPRECATED_ATTRIBUTE;
/**
 METHOD IS DEPRECATED FROM v1.8.5(34)
 use 'initWithViewController:(id)viewController recipeId:(NSString *)recipeId;'
 */
-(id)initWithViewController:(id)viewController environment:(int)type productionRecipeId:(NSString *)pRecipeId stagingRecipeId:(NSString *)sRecipeId DEPRECATED_ATTRIBUTE;
@end
