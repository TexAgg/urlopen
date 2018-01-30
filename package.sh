# Creates a .deb package.

NAUTILUS_ACTION='urlopen_action.desktop'
# DON'T FORGET TO KEEP THIS UP TO DATE WITH urlopen.1 and CMakeLists.txt
VERSION=3.0.1

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

# Icon for each size (see https://github.com/TexAgg/urlopen/issues/1).
for i in 256 128 64 48 32 24 22 16
do
	mkdir -p $TEMPDIR/usr/share/icons/Humanity/mimes/${i}
	cp -t $TEMPDIR/usr/share/icons/Humanity/mimes/${i} img/application-x-mswinurl.svg
done

cp -t $TEMPDIR ${NAUTILUS_ACTION}

# Create a temporary file with the post-install script.
TEMP=$(mktemp -p .)
# https://stackoverflow.com/a/23930212/5415895
cat > $TEMP <<- EOM
echo "application/x-mswinurl=urlopen.desktop" >> $HOME/.local/share/applications/mimeapps.list
echo "application/x-mswinurl url" | sudo tee -a /etc/mime.types
sudo gtk-update-icon-cache /usr/share/icons/Humanity

mv ${NAUTILUS_ACTION} \${HOME}/Downloads
echo "Import the file ${NAUTILUS_ACTION} with nautilus-actions to view the url."
EOM

# Create another temporary file with the post-remove script.
TEMP2=$(mktemp -p .)
cat > $TEMP2 <<- EOM
sed -i 's/\<application\/x-mswinurl=urlopen.desktop\>//g' \${HOME}/.local/share/applications/mimeapps.list
sudo sed -i "s/\<application\/x-mswinurl url\>//g" /etc/mime.types
EOM

fpm -s dir -t deb -n "urlopen" -f --after-install $TEMP -v $VERSION \
	--after-remove $TEMP2 \
	--depends nautilus-actions \
	--deb-build-depends build-essential \
	--description "A tool for opening windows' internet shortcut files." \
	--maintainer "mgaikema1@protonmail.com" \
	--url "https://github.com/TexAgg/urlopen" \
	-C $TEMPDIR .

rm $TEMP
rm $TEMP2
rm -r $TEMPDIR