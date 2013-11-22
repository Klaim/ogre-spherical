ogre-spherical
==============

Spherical coordinates representation and utility for Ogre 3D graphic engine.

Dependencies
============

This code depends on Ogre's maths features.

How To Use
==========

The simplest way is to copy-paste the sources into your project's code,
assuming Ogre's headers are available for this project's sources.

However, if you need to use this code into multiple projects, there are several 
other ways:

 1. make a static library from this code;
 2. have one shared library contain and expose this code;

In the second case, you will need add a symbol impot/export macro
to the class or to the static constants it contains, in the header only.

