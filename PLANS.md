# File structure 
gravemanager/

ntr subfolder with:
- saves
- config.json

twl subfolder with:

- saves
- config.json

in the config.json there should be a link, to the file of every game in the saves folder.

[nds-bootstrap](https://github.com/DS-Homebrew/nds-bootstrap), as far as I know, saves in a saves subfolder for games with the same name.

ds type files scanned for will be nds, dsi, srl, ids and app, as to
[ds-homebrew wiki](https://wiki.ds-homebrew.com/ds-index/emulators.html) (viewed on 1693773446 (unix timestamp))

depending on the save extension, theyll be split up into ntr and twl. 

ctr subfolder with:

- saves
- extdata
- config.json

sys subfolder with:

- saves
- extdata
config.json

# system file permissions

There will be 4 tabs, 3ds, nds, dsiware and sys
In order to get access to the sys tab, you have to input a key combo telling you that it can softbrick your 3ds etc

