# ----------------------------
# Set NAME to the program name
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ----------------------------

NAME        ?= SRVCEMAP
COMPRESSED  ?= NO
ICON        ?= icon.png
DESCRIPTION ?= "SurvivalCE Map Maker Tool"

# ----------------------------

include $(CEDEV)/include/.makefile
