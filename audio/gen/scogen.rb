#
# Copyright (C) 2018 Vibbro
#
require 'frequencies'

Vibbro::FREQUENCIES.each do
  |vf|
  outfilename= "frq_gen_%03d.sco" % [ vf ]

  File.open(outfilename, 'w') do
    |fh|
    fh.print <<-EOF
;
; Copyright (C) 2018 Vibbro
;
#include "tables.inc"

i1 0 120 -1 #{vf} 8 30
EOF
  end
end
