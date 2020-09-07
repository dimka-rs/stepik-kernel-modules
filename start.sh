#!/bin/sh
[ -n "$1" ] && DEBUG="--debug"
vagrant up --provider=libvirt $DEBUG

