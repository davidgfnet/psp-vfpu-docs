
PSP VFPU documentation
======================

This is an attempt to a full VFPU documentation for Sony's MIPS Allegrex CPU,
the main CPU of Sony's PSP.

Current documentation is incomplete, scattered all over the internet (in some
forums, personal websites, github repos and projects, etc) and, in many cases,
contradictory. As opposed to other devices (like the PS2 console) Sony did not
release any public documentation (nor SDK/toolchain) for the Sony PSP. For
this reason we've attempted to collect all these documents and distil a usable
set of documents that can be used by coders, hombrew devs, and anyone
interested in writing VFPU assembly.

Since there's some gaps in knowledge as well as contradictions, this
documentation is designed so that it can be verified. All instructions are
described in `inst-desc.yaml`: encoding, operands, valid prefixes, precision,
register collisions and, most importantly, functional description. For each of
these statements there's a test that can be executed on a PSP device to
validate it. Some tests are manually crafted whereas the majority are
autogenerated from the YAML description. Major tests exist for:

  - Functional description (pseudo C code)
  - Prefix compatibility
  - Register overlap restrictions
  - Calculation accuracy
  - Performance (throughput and latency)

With these tests in place, we can be reasonably sure of the statements
described in the docs. For convenience and consistency we also generate most
of the actual documentation from this YAML description, so that any change in
the formal description is reflected both in the human-readable docs and the
tests.

The main assets created by this repo are the tests (which are mostly for
internal consumption) and the documentation itself, in HTML and PDF format.


Building docs and tests
-----------------------

You can generate the docs in HTML and PDF format by running `make docs`. This
requires `weasyprint` as well as a few python modules such as `mako`, `pyyaml`,
`markdown` and `tatsu`.

To build the tests a recent [PSP toolchain](https://github.com/pspdev/pspdev)
is required. You will need to follow the SDK instructions (that is, set PSPDEV
and PATH environment variables before running any make rules). You can just
run `make psptests` to get EBOOT.PBP binaries (or, as usual, run
`make psptests BUILD_PRX=1` to get .prx modules). We recommend running build
parallel (`-jN`) since tests are pretty big and take a while to build.

Some tests are autogenerated (but also checked-in in the repo), you might
re-generate them (ie. if you want to update the instruction description) by
running `make tests`. It is recommended to install `clang-format` to produce
readable test files. Tests are generally deterministic to avoid random data
changing on every build.


