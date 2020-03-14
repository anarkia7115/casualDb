bazel query --notool_deps --noimplicit_deps 'deps(//main:casualdb)' \
  --output graph
