#!/bin/sh
premake4 vs2005
premake4 vs2008
premake4 vs2010
premake4 gmake
sed -i '' -E 's:(-L/usr/lib(32|64))|(-Wl,-x)::g' gmake/*.make
