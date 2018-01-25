# Creates a .deb package.

# Create temporary directory for packaging.
TEMPDIR=$(mktemp -d -p .)

mkdir -p $TEMPDIR/usr/local/bin
cp -t $TEMPDIR/usr/local/bin _build/urlopen

mkdir -p $TEMPDIR/usr/share/applications
cp -t $TEMPDIR/usr/share/applications urlopen.desktop

mkdir -p $TEMPDIR/usr/local/man/man1
cp -t $TEMPDIR/usr/local/man/man1 urlopen.1

mkdir -p $TEMPDIR/usr/share/pixmaps
cp -t $TEMPDIR/usr/share/pixmaps img/urlopen_64x64.png

mkdir -p $TEMPDIR/usr/share/icons/humanity/mimes/256
cp -t $TEMPDIR/usr/share/icons/humanity/mimes/256 img/application-x-mswinurl.svg

# DON'T FORGET TO KEEP THIS UP TO DATE WITH urlopen.1 and CMakeLists.txt
VERSION=3.0.0

# Create a temporary file with the preinstall script.
TEMP=$(mktemp -p .)
# https://stackoverflow.com/a/23930212/5415895
cat > $TEMP <<- EOM
echo "application/x-mswinurl=urlopen.desktop" >> $HOME/.local/share/applications/mimeapps.list
echo "application/x-mswinurl url" | sudo tee -a /etc/mime.types
sudo gtk-update-icon-cache /usr/share/icons/Humanity
EOM

# Create another temporary file with the post-remove script.
TEMP2=$(mktemp -p .)
cat > $TEMP2 <<- EOM
sed -i 's/\<application\/x-mswinurl=urlopen.desktop\>//g' $HOME/.local/share/applications/mimeapps.list
sudo sed -i "s/\<application\/x-mswinurl url\>//g" /etc/mime.types
EOM

fpm -s dir -t deb -n "urlopen" --after-install $TEMP -v $VERSION \
	--after-remove $TEMP2 \
	--deb-build-depends build-essential \
	--description "A tool for opening windows' internet shortcut files." \
	--maintainer "mgaikema1@protonmail.com" \
	--url "https://github.com/TexAgg/urlopen" \
	-C $TEMPDIR .

rm $TEMP
rm $TEMP2
rm -r $TEMPDIR