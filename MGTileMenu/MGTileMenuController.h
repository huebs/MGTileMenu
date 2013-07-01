//
//  MGTileMenuController.h
//  MGTileMenu
//
//  Created by Matt Gemmell on 27/01/2012.
//  Copyright (c) 2012 Instinctive Code.
//

#import <UIKit/UIKit.h>
#import "MGTileMenuDelegate.h"

@interface MGTileMenuController : UIViewController

@property (nonatomic, weak, readonly)	id<MGTileMenuDelegate>		delegate;		// Must be specified via initializer method.
@property (nonatomic, readonly)			CGPoint						centerPoint;	// In parent view's coordinate system.
																					// If menu not visible, will be CGPointZero.
@property (nonatomic, weak, readonly)	UIView						*parentView;
@property (nonatomic, readonly)			BOOL						isVisible;
@property (nonatomic, readonly)			NSInteger					currentPage;	// zero-based

// N.B. All of the following properties should be set BEFORE displaying the menu.

@property (nonatomic) BOOL				dismissAfterTileActivated;					// Automatically dismiss menu after a tile is activated (YES; default)
@property (nonatomic) BOOL				rightHanded;								// Leave gap for right-handed finger (YES; default) or left-handed (NO)
@property (nonatomic) BOOL				shadowsEnabled;								// Whether to draw shadows below bezel and tiles (default: YES)

@property (nonatomic) NSInteger			tileSide;									// Width and height of each tile, in pixels (default 72 pixels)
@property (nonatomic) NSInteger			tileGap;									// Horizontal and vertical gaps between tiles, in pixels (default: 20 pixels)
@property (nonatomic) CGFloat			cornerRadius;								// Corner radius for bezel and all tiles, in pixels (default: 12.0 pixels)
@property (nonatomic) CGGradientRef		tileGradient;								// Gradient to apply to tile backgrounds (default: a lovely blue)
@property (nonatomic) NSInteger			selectionBorderWidth;						// Default: 5 pixels
@property (nonatomic) CGGradientRef		selectionGradient;							// Default: a subtle white (top) to grey (bottom) gradient

@property (nonatomic, strong) UIColor	*bezelColor;								// Color of the background bezel/HUD; default: black, 50% opaque
@property (nonatomic, strong) UIImage	*closeButtonImage;							// Default: nil (which renders a Home Screen-like "X" button)
@property (nonatomic, strong) UIImage	*selectedCloseButtonImage;					// Default: nil (as above)
@property (nonatomic, strong) UIImage	*pageButtonImage;							// Default: nil (which renders an ellipsis "...")

@property (nonatomic) BOOL shouldMoveToStayVisibleAfterRotation;					// Whether the menu should automatically move to remain fully visible
																					// after the device has been rotated (default: YES)
@property (nonatomic) BOOL closeButtonVisible;										// Whether the close button is visible (default: YES).
																					// If NO, the user can still dismiss the menu by tapping outside its
																					// bounds (which you can also disable via the tileMenuShouldDismiss:
																					// delegate method)

#pragma mark - Creation

- (id)initWithDelegate:(id<MGTileMenuDelegate>)theDelegate;			// Required parameter; cannot be nil.

// Display the menu. Returns the actual center-point used (may be shifted from centerPt to fit fully on-screen, if possible).

- (CGPoint)displayMenuCenteredOnPoint:(CGPoint)centerPt
							   inView:(UIView *)parentView;

// As above, with the menu already displaying the specified 'page' of tiles.

- (CGPoint)displayMenuPage:(NSInteger)pageNum
		   centeredOnPoint:(CGPoint)centerPt
					inView:(UIView *)parentView;

// Immediately dismiss/hide the menu, cancelling further interaction.

- (void)dismissMenu;

// Switch to the specified 'page' of items, if possible.
- (void)switchToPage:(NSInteger)pageNum; // zero-based pageNum
- (void)goToNextPage; // action for the page-switching tile.

#pragma mark - Utilities

CGRect MGMinimallyOverlapRects(CGRect inner, CGRect outer, CGFloat padding);
CGPoint MGCenterPoint(CGRect rect);
CGGradientRef MGCreateGradientWithColors(UIColor *topColorRGB, UIColor *bottomColorRGB); // assumes colors in RGB colorspace

- (NSInteger)nextPageNumber:(NSInteger)currentPageNumber;	// zero-based pageNumber
- (UIBezierPath *)_bezelPath;
- (CGRect)frameForTileAtIndex:(NSInteger)tileNumber;		// zero-based tileNumber, 0-5 (excludes central Close button position)
- (CGRect)frameForCenteredTile;

- (UIImage *)tileBackgroundImageHighlighted:(BOOL)highlighted;
- (UIImage *)tileBackgroundImageForTile:(NSInteger)tileNumber
							highlighted:(BOOL)highlighted;

- (void)tileActivated:(id)sender;	// action for when each tile is actually activated/chosen, switched on tag index.
- (void)tileSelected:(id)sender;	// action for when each tile is highlighted, switched on tag index.
- (void)tileDeselected:(id)sender;	// action for each tile is unhighlighted, switched on tag index.

- (void)animateTilesForCurrentPage;
- (void)setAllTilesInteractionEnabled:(BOOL)enabled;

@end

#pragma mark - Notifications

// All of the following notifications have an `object' that is the sending MGTileMenuController.

extern NSString *MGTileMenuWillDisplayNotification;			// menu will be shown
extern NSString *MGTileMenuDidDisplayNotification;			// menu has been shown
extern NSString *MGTileMenuWillDismissNotification;			// menu will be dismissed
extern NSString *MGTileMenuDidDismissNotification;			// menu has been dismissed

// The following notifications have a user info key "MGTileNumber" with an NSNumber (integer, zero-based) value.

#define MGTileNumberKey @"MGTileNumber"

extern NSString *MGTileMenuDidActivateTileNotification;		// tile was activated/triggered
extern NSString *MGTileMenuDidSelectTileNotification;		// tile was highlighted, but not yet triggered
extern NSString *MGTileMenuDidDeselectTileNotification;		// tile was unhighlighted, without being triggered

// The following notifications have a user info key "MGPageNumber" with an NSNumber (integer, zero-based) value.

#define MGPageNumberKey @"MGPageNumber"

extern NSString *MGTileMenuWillSwitchToPageNotification;	// menu will switch to the given page
extern NSString *MGTileMenuDidSwitchToPageNotification;		// menu did switch to the given page
