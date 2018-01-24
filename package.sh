# Creates a .deb package.

# DON'T FORGET TO KEEP THIS UP TO DATE WITH urlopen.1 and CMakeLists.txt
VERSION=3.0.0
ARCHIVE=temp.tar
FILES="img/urlopen_64x64.png urlopen.1 urlopen.desktop "
tar --create --file=$ARCHIVE --exclude-vcs --exclude=_build/* \
	--exclude=.vscode/ --exclude=*.tar --exclude=package.sh *

# Create a temporary script with the preinstall script.
TEMP=temp.sh
# https://stackoverflow.com/a/23930212/5415895
cat > $TEMP <<- EOM
cd _build
cmake ../
make
sudo bash setup.sh
EOM

TEMP2=temp2.sh
cat > $TEMP2 <<- EOM
cd _build
rm -rf *
EOM

fpm -s tar -t deb -n "urlopen" --after-install $TEMP -v $VERSION \
	--after-remove uninstall.sh \
	--before-remove $TEMP2 \
	--deb-build-depends build-essential \
	--description "A tool for opening windows' internet shortcut files." \
	--maintainer "mgaikema1@protonmail.com" \
	--url "https://github.com/TexAgg/urlopen" \
	$ARCHIVE

rm $ARCHIVE
rm $TEMP
rm $TEMP2