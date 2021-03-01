-off 0xFFFC0000
-entry start

start:
    mv mri, interrupt_table
    mv orl, mrf
    mv orr, 2
    mv mrf, bro
    mv mre, 0x80000000
    mv mrp, mrp

interrupt_table:
    x31 dd 0
    dd interface_interrupt_handler

interface_interrupt_handler:
    mv prs, prb
    mv orl, prs
    mv orr, 4
    mv mrp, d ars    
