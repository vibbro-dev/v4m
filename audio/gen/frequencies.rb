#
# Copyright (C) 2018 Vibbro
#
VIBBRO_FP= File.expand_path(File.join(['..'] * 5, 'v4m-vibbro', 'constants', 'frequencies'), __FILE__)

if File.exists?(VIBBRO_FP)
  require VIBBRO_FP
else
  module Vibbro

    FREQUENCIES = [ 23, 33 ]

  end
end
