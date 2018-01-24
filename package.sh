# Creates a .deb package.

TEMPDIR=urlopen_temp
rm -rf $TEMPDIR
mkdir $TEMPDIR
cp -r -t $TEMPDIR CMakeLists.txt *.cpp *.hpp urlopen.1 urlopen.desktop img/ simpleini/ argparse/
mkdir $TEMPDIR/_build

# DON'T FORGET TO KEEP THIS UP TO DATE WITH urlopen.1 and CMakeLists.txt
VERSION=3.0.0

# Create a temporary script with the preinstall script.
TEMP=temp.sh
# https://stackoverflow.com/a/23930212/5415895
cat > $TEMP <<- EOM
cd ${TEMPDIR}
cd _build
cmake ../
make
sudo bash setup.sh
EOM

TEMP2=temp2.sh
cat > $TEMP2 <<- EOM
rm ${TEMPDIR}/_build/*
EOM

fpm -s dir -t deb -n "urlopen" --after-install $TEMP -v $VERSION \
	--after-remove uninstall.sh \
	--before-remove $TEMP2 \
	--deb-build-depends build-essential \
	--description "A tool for opening windows' internet shortcut files." \
	--maintainer "mgaikema1@protonmail.com" \
	--url "https://github.com/TexAgg/urlopen" \
	$TEMPDIR

rm $TEMP
rm $TEMP2
rm -r $TEMPDIR