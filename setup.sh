# Install urlopen and make it the default application for opening url files.
# http://bit.ly/2F56uay

# Build and install the files.
sudo make install
# Make urlopen the default application for opening url files.
echo "application/x-mswinurl=urlopen.desktop" >> $HOME/.local/share/applications/mimeapps.list

# https://askubuntu.com/a/56725/574988
echo "application/x-mswinurl url" | sudo tee -a /etc/mime.types

# Update icon cache.
sudo gtk-update-icon-cache /usr/share/icons/Humanity