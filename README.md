# Float32AVRTest
This repository contains reference examples of floating-point calculations. The results from these examples will be compared against a custom software floating-point emulation for AVR from [this repo](https://github.com/igor-240340/Float32AVR).

The idea is to use the hardware implementation of IEEE 754 on a desktop as the reference. We calculate reference results and compare them with those returned by our custom software emulation.

The numbering of examples is cross-referenced: example number 1 in this repository corresponds to example number 1 in Float32AVR and to example number 1 in the mind map analyzing possible cases (the mind map files with extension `*.xmind` can be found in docs directory in the repo of the main project Hardware Calculator From Scratch [here](https://github.com/igor-240340/HardwareCalculatorFromScratch/tree/en/docs/Basic%20Research%20Notes)).

One caveat: Float32AVR does not support `inf`, `nan`, or denormalized numbers. Therefore:
- For examples where the hardware floating-point implementation returns `inf` or `nan`, Float32AVR will throw an exception.  
- For cases where a denormalized number is returned, Float32AVR will return zero.
