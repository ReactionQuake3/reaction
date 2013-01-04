#!/bin/sh
CC=gcc-4.0
APPBUNDLE=Reaction.app
BINARY=Reaction.ub
DEDBIN=Reactionded.ub
PKGINFO=APPLIOQ3
ICNS=misc/quake3.icns
DESTDIR=build/release-darwin-ub
BASEDIR=Boomstick
MPACKDIR=missionpack
LANG=C
LC_ALL=C

BIN_OBJ="
	build/release-darwin-x86_64/Reaction.x86_64
	build/release-darwin-i386/Reaction.i386
"
BIN_DEDOBJ="
	build/release-darwin-x86_64/Reactionded.x86_64
	build/release-darwin-i386/Reactionded.i386
"
BASE_OBJ="
	build/release-darwin-x86_64/$BASEDIR/cgamex86_64.dylib
	build/release-darwin-i386/$BASEDIR/cgamei386.dylib
	build/release-darwin-x86_64/$BASEDIR/uix86_64.dylib
	build/release-darwin-i386/$BASEDIR/uii386.dylib
	build/release-darwin-x86_64/$BASEDIR/qagamex86_64.dylib
	build/release-darwin-i386/$BASEDIR/qagamei386.dylib
"
MPACK_OBJ="
	build/release-darwin-x86_64/$MPACKDIR/cgamex86_64.dylib
	build/release-darwin-i386/$MPACKDIR/cgamei386.dylib
	build/release-darwin-x86_64/$MPACKDIR/uix86_64.dylib
	build/release-darwin-i386/$MPACKDIR/uii386.dylib
	build/release-darwin-x86_64/$MPACKDIR/qagamex86_64.dylib
	build/release-darwin-i386/$MPACKDIR/qagamei386.dylib
"
RENDER_OBJ="
	build/release-darwin-x86_64/renderer_opengl1_smp_x86_64.dylib
	build/release-darwin-i386/renderer_opengl1_smp_i386.dylib
	build/release-darwin-x86_64/renderer_opengl1_x86_64.dylib
	build/release-darwin-i386/renderer_opengl1_i386.dylib
	build/release-darwin-x86_64/renderer_rend2_smp_x86_64.dylib
	build/release-darwin-i386/renderer_rend2_smp_i386.dylib
	build/release-darwin-x86_64/renderer_rend2_x86_64.dylib
	build/release-darwin-i386/renderer_rend2_i386.dylib
"

cd `dirname $0`
if [ ! -f Makefile ]; then
	echo "This script must be run from the Reaction build directory"
	exit 1
fi

Q3_VERSION=`grep '^VERSION=' Makefile | sed -e 's/.*=\(.*\)/\1/'`

# we want to use the oldest available SDK for max compatiblity
unset X86_64_SDK
unset X86_64_CFLAGS
unset X86_64_LDFLAGS
unset X86_SDK
unset X86_CFLAGS
unset X86_LDFLAGS
if [ -d /Developer/SDKs/MacOSX10.5.sdk ]; then
	X86_64_SDK=/Developer/SDKs/MacOSX10.5.sdk
	X86_64_CFLAGS="-arch x86_64 -isysroot /Developer/SDKs/MacOSX10.5.sdk \
			-DMAC_OS_X_VERSION_MIN_REQUIRED=1050"
	X86_64_LDFLAGS=" -mmacosx-version-min=10.5"

	X86_SDK=/Developer/SDKs/MacOSX10.5.sdk
	X86_CFLAGS="-arch i386 -isysroot /Developer/SDKs/MacOSX10.5.sdk \
			-DMAC_OS_X_VERSION_MIN_REQUIRED=1050"
	X86_LDFLAGS=" -mmacosx-version-min=10.5"
fi

# The 10.4 SDK is not 64 bit ready and can not be used to build 64bit versions.
# This makes 10.5 the minimum for UB's containing x86_64
#
#if [ -d /Developer/SDKs/MacOSX10.4u.sdk ]; then
#	X86_64_SDK=/Developer/SDKs/MacOSX10.4u.sdk
#	X86_64_CFLAGS="-arch x86_64 -isysroot /Developer/SDKs/MacOSX10.4u.sdk \
#			-DMAC_OS_X_VERSION_MIN_REQUIRED=1040"
#	X86_64_LDFLAGS=" -mmacosx-version-min=10.4"
#
#	X86_SDK=/Developer/SDKs/MacOSX10.4u.sdk
#	X86_CFLAGS="-arch i386 -isysroot /Developer/SDKs/MacOSX10.4u.sdk \
#			-DMAC_OS_X_VERSION_MIN_REQUIRED=1040"
#	X86_LDFLAGS=" -mmacosx-version-min=10.4"
#fi
#
#if [ -d /Developer/SDKs/MacOSX10.3.9.sdk ] && [ $TIGERHOST ]; then
#	X86_64_SDK=/Developer/SDKs/MacOSX10.3.9.sdk
#	X86_64_CFLAGS="-arch x86_64 -isysroot /Developer/SDKs/MacOSX10.3.9.sdk \
#			-DMAC_OS_X_VERSION_MIN_REQUIRED=1030"
#	X86_64_LDFLAGS=" -mmacosx-version-min=10.3"
#fi

if [ -z $X86_64_SDK ] || [ -z $X86_SDK ]; then
	echo "\
ERROR: This script is for building a Universal Binary.  You cannot build
       for a different architecture unless you have the proper Mac OS X SDKs
       installed.  If you just want to to compile for your own system run
       'make' instead of this script."
	exit 1
fi

echo "Building X86_64 Client/Dedicated Server against \"$X86_64_SDK\""
echo "Building X86 Client/Dedicated Server against \"$X86_SDK\""
echo
if [ "$X86_64_SDK" != "/Developer/SDKs/MacOSX10.5.sdk" ] || \
	[ "$X86_SDK" != "/Developer/SDKs/MacOSX10.5.sdk" ]; then
	echo "\
WARNING: in order to build a binary with maximum compatibility you must
         build on Mac OS X 10.5 using Xcode 3.1 and have the MacOSX10.5
         SDKs installed from the Xcode install disk Packages folder."
sleep 3
fi

if [ ! -d $DESTDIR ]; then
	mkdir -p $DESTDIR
fi

# For parallel make on multicore boxes...
NCPU=`sysctl -n hw.ncpu`

# x86_64 client and server
if [ -d build/release-release-x86_64 ]; then
	rm -r build/release-darwin-x86_64
fi
(ARCH=x86_64 CC=gcc-4.0 CFLAGS=$X86_64_CFLAGS LDFLAGS=$X86_64_LDFLAGS make -j$NCPU) || exit 1;

echo;echo;echo

# i386 client and server
if [ -d build/release-darwin-i386 ]; then
	rm -r build/release-darwin-i386
fi
(ARCH=i386 CC=gcc-4.0 CFLAGS=$X86_CFLAGS LDFLAGS=$X86_LDFLAGS make -j$NCPU) || exit 1;

echo;echo;echo

echo "Creating .app bundle $DESTDIR/$APPBUNDLE"
if [ ! -d $DESTDIR/$APPBUNDLE/Contents/MacOS/$BASEDIR ]; then
	mkdir -p $DESTDIR/$APPBUNDLE/Contents/MacOS/$BASEDIR || exit 1;
fi
if [ ! -d $DESTDIR/$APPBUNDLE/Contents/MacOS/$MPACKDIR ]; then
	mkdir -p $DESTDIR/$APPBUNDLE/Contents/MacOS/$MPACKDIR || exit 1;
fi
if [ ! -d $DESTDIR/$APPBUNDLE/Contents/Resources ]; then
	mkdir -p $DESTDIR/$APPBUNDLE/Contents/Resources
fi
cp $ICNS $DESTDIR/$APPBUNDLE/Contents/Resources/Reaction.icns || exit 1;
echo $PKGINFO > $DESTDIR/$APPBUNDLE/Contents/PkgInfo
echo "
	<?xml version=\"1.0\" encoding=\"UTF-8\"?>
	<!DOCTYPE plist
		PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\"
		\"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">
	<plist version=\"1.0\">
	<dict>
		<key>CFBundleDevelopmentRegion</key>
		<string>English</string>
		<key>CFBundleExecutable</key>
		<string>$BINARY</string>
		<key>CFBundleGetInfoString</key>
		<string>Reaction 1.0</string>
		<key>CFBundleIconFile</key>
		<string>Reaction.icns</string>
		<key>CFBundleIdentifier</key>
		<string>org.ioquake.Reaction</string>
		<key>CFBundleInfoDictionaryVersion</key>
		<string>6.0</string>
		<key>CFBundleName</key>
		<string>Reaction</string>
		<key>CFBundlePackageType</key>
		<string>APPL</string>
		<key>CFBundleShortVersionString</key>
		<string>$Q3_VERSION</string>
		<key>CFBundleSignature</key>
		<string>$PKGINFO</string>
		<key>CFBundleVersion</key>
		<string>$Q3_VERSION</string>
		<key>NSExtensions</key>
		<dict/>
		<key>NSPrincipalClass</key>
		<string>NSApplication</string>
	</dict>
	</plist>
	" > $DESTDIR/$APPBUNDLE/Contents/Info.plist

# Change the path of the SDL Framework in both arches for the executables and renderer dylib's
for i in $BIN_OBJ $BIN_DEDOBJ $RENDER_OBJ
do
	install_name_tool -change "@rpath/SDL.framework/Versions/A/SDL" "@executable_path/../Frameworks/SDL.framework/Versions/A/SDL" $i
done

# Make UB's from previous builds of 1386 and x86_64 binaries
lipo -create -o $DESTDIR/$APPBUNDLE/Contents/MacOS/$BINARY $BIN_OBJ
lipo -create -o $DESTDIR/$APPBUNDLE/Contents/MacOS/$DEDBIN $BIN_DEDOBJ

# Embed the SDL framework into the .app so players done need to install it on their systems.
mkdir $DESTDIR/$APPBUNDLE/Contents/Frameworks
unzip -d $DESTDIR/$APPBUNDLE/Contents/Frameworks code/libs/macosx/SDL-1.2.15.framework.zip

# Change the path in the UB, just in case
install_name_tool -change "@rpath/SDL.framework/Versions/A/SDL" "@executable_path/../Frameworks/SDL.framework/Versions/A/SDL" $DESTDIR/$APPBUNDLE/Contents/MacOS/$BINARY
install_name_tool -change "@rpath/SDL.framework/Versions/A/SDL" "@executable_path/../Frameworks/SDL.framework/Versions/A/SDL" $DESTDIR/$APPBUNDLE/Contents/MacOS/$DEDBIN

cp $RENDER_OBJ $DESTDIR/$APPBUNDLE/Contents/MacOS/
cp $BASE_OBJ $DESTDIR/$APPBUNDLE/Contents/MacOS/$BASEDIR/
#cp $MPACK_OBJ $DESTDIR/$APPBUNDLE/Contents/MacOS/$MPACKDIR/
cp code/libs/macosx/*.dylib $DESTDIR/$APPBUNDLE/Contents/MacOS/

