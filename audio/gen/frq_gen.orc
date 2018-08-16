;
; Copyright (C) 2018 Vibbro
;
; These files generate the waves for the vibed bed
;
    sr=48000
    ksmps=1
    nchnls=2
    0dbfs=1


    instr 1
iamp      = ampdb(p4)
ifreq     = p5
ifdelta   = p6
          print iamp

ifenvdur  = p3
icenvdur  = p7

icenvfrq  = 1/icenvdur

irise     = ifenvdur/20
ifall     = ifenvdur/20

kcenvl    oscili  1, icenvfrq, 2
kcenvr    = 1 - kcenvl
aleft     oscili  iamp, ifreq, 1
aright    oscili  iamp, ifreq+ifdelta, 1

aleft     linen   aleft*kcenvl, irise, ifenvdur, ifall
aright    linen   aright*kcenvr, irise, ifenvdur, ifall

          outs    aleft, aright


    endin
