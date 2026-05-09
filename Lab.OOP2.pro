TEMPLATE = subdirs

SUBDIRS = \
    LinkManagerCore \
    OOP2Lab \
    LinkManagerTest

OOP2Lab.depends = LinkManagerCore
LinkManagerTest.depends = LinkManagerCore