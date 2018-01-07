# Install urlopen and make it the default application for opening url files.
# http://bit.ly/2F56uay

sudo make install
echo "application/x-mswinurl=urlopen.desktop" >> $HOME/.local/share/applications/mimeapps.list