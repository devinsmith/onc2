# onc2

onc2 is a chat client with a GUI for Michael Kohn's Nakenchat (www.naken.cc).

# Building
Under Ubuntu you will need libwxgtk3.0-dev to build.

```
sudo apt-get install libwxgtk3.0-dev
```

VoidLinux packages both wxWidgets gtk2 and gtk3 support

```
# Gtk2
sudo xbps-install -Su wxWidgets-devel
# Gtk3
sudo xbps-install -Su wxWidgets-gtk3-devel

```

You should then edit the Makefile to target gtk2 or gtk3.
