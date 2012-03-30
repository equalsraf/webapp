
WebApp is a web application container that turns web pages into desktop
applications.

# Build instructions

WebApp requires Qt and QJson to work. To build it use qmake.
For example in \*nix systems with make, you would:

    $ qmake
    $ make

# How does it work?

Just call

    $ webapp <configfile>

Each webapp is described as a JSon config file. Check the examples directory
for a few samples.


# Features

At this point the following features are supported:

* Restrict view to certain hosts, or wildcard domains
* Disable Javascript


