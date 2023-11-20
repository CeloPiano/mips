# MIPS Assembly Problem

.data
    array:  .word 1232222, 23, 322, 44, 55
    result: .word 0

.text
    main:
        # Load a word from memory into a register
        lw $t0, array($zero)

        # Load a byte from memory into a register
        lb $t1, array($zero)

        # Load an unsigned byte from memory into a register
        lbu $t2, array($zero)

        # Load a halfword from memory into a register
        lh $t3, array($zero)

        # Load an unsigned halfword from memory into a register
        lhu $t4, array($zero)

        # Load an immediate value into the upper 16 bits of a register
        lui $t5, 0x1234

        # Store a word from a register into memory
        sw $t0, result($zero)

        # Store a byte from a register into memory
        sb $t1, result($zero)

        # Store a halfword from a register into memory
        sh $t3, result($zero)

        # Add an immediate value to a register
        addi $t0, $t0, 10

        # Set a register to 1 if less than immediate, else 0
        slti $t1, $t0, 5

        # Set a register to 1 if less than immediate (unsigned), else 0
        sltiu $t2, $t0, 5

        # Bitwise AND with an immediate value
        andi $t3, $t0, 0xFF

        # Bitwise OR with an immediate value
        ori $t4, $t0, 0xFF

        # Bitwise XOR with an immediate value
        xori $t5, $t0, 0xFF
	
	# Branch if two registers are equal
        beq $t0, $t1, equal_label

equal_label_back:
        # Branch if two registers are not equal
        bne $t0, $t1, not_equal_label

not_equal_label_back:
        # Branch if less than or equal to zero
        blez $t0, less_equal_zero_label

less_equal_zero_label_back:
        # Branch if greater than zero
        bgtz $t0, greater_zero_label
	
greater_zero_label_back:	
        # Jump to a target address
        jal jump_label
jump_label_back:
	li $v0, 10
	syscall

    equal_label:
        # Code for equal case
        ...
        jal equal_label_back

    not_equal_label:
        # Code for not equal case
        ...
        jal not_equal_label_back

    less_equal_zero_label:
        # Code for less than or equal to zero case
        ...
        jal less_equal_zero_label_back

    greater_zero_label:
        # Code for greater than zero case
        ...
        jal greater_zero_label_back

    jump_label:
        # Code for jump target
        ...
        jal jump_label_back
