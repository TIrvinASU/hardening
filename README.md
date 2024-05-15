Background:

This covers the work that I performed for our Capstone project - Hardening Linux OS. Our project was sponsored by General Dynamics and focused on securing Linux for a secure communications device.

The main channel we focused on in pursuit of hardening Linux was removing unnecessary devices in the device tree for the hardware board our sponsor will use in their end product. Removing unnecessary devices reduces the amount of drivers that can be loaded, reducing the chance a malicious driver - particularly third party drivers not focused on in development of this product - compromises the system. 

This process can be grouped into three general steps:
    Identifying the relevant devices that are unnecessary and can be removed
    Removing those devices from the device tree and verifying they have been removed
    Performing regression testing

My personal work centered identifying which devices could be removed, and perform regression for the subset of removed devices I was assigned. 

Future work for this project could include:
    Integrating each team member's tests into a single test script
    Making the tests performed more thorough (ex: for the DMA I removed, testing could be expanded to an actual demonstration of the functionality the end product will use, transferring incoming audio data to the speaker device, or video data to the display port)
    Other means of hardening Linux OS:
        closing unused network ports
        disabling shell access where its not needed
        etc