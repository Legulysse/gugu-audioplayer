# ***    Config  ***#

TEMPLATE = subdirs
SUBDIRS =   LibPugiXml \
            LibSfml \
            LibEngine \
            LibAudioPlayer

# build must be last:
CONFIG += ordered
SUBDIRS += Build
