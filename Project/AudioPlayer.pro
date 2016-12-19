# ***    Config  ***#

TEMPLATE = subdirs
SUBDIRS =   LibSfml \
            LibEngine \
            LibAudioPlayer

# build must be last:
CONFIG += ordered
SUBDIRS += Build
