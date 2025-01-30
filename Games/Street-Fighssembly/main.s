.global _start
.align 2

_start:
    // Set screen resolution using the mailbox interface
    ldr x0, =mailbox_message  // Address of the message buffer
    bl mailbox_call           // Send request to GPU

    // Read framebuffer address (GPU returns it in mailbox_message + 20)
    ldr x1, =mailbox_message + 20
    ldr x21, [x1]             // Store framebuffer address

    // Draw a red rectangle
    mov x0, x21              // Start of framebuffer
    mov x1, 0x00FF0000       // Red color (ARGB)
    mov x2, 50000            // Loop counter (number of pixels)
draw_loop:
    str w1, [x0], #4         // Store color, move to next pixel
    subs x2, x2, #1          // Decrement counter
    b.ne draw_loop

    // Exit
    mov x8, 93               // syscall exit
    mov x0, 0
    svc #0

// ---------------------------------------------
// Mailbox Call Function
// ---------------------------------------------
mailbox_call:
    mov x2, #0x3F00B880      // Mailbox Base Register
    mov x3, #0x80000000      // Channel 8 (Property Interface)
    
    // Write to Mailbox Register
    str x0, [x2, #0]         // Write address to Mailbox0 Write Register
wait_response:
    ldr x4, [x2, #0x18]      // Read Mailbox0 Status Register
    tst x4, #0x40000000      // Check if Mailbox is empty
    b.ne wait_response       // If empty, keep waiting

    ldr x4, [x2, #0]         // Read Mailbox0 Read Register
    cmp x4, x3              // Check if response is for us
    b.ne wait_response       // If not, wait again
    ret                     // Return to caller


mailbox_message:
    .word 8 * 4             // Total message size
    .word 0                 // Request/Response code
    .word 0x00048003        // Tag: Set Physical Display
    .word 8                 // Value buffer size
    .word 8                 // Request size
    .word 800               // Width
    .word 600               // Height
    .word 0x00040001        // Tag: Allocate Framebuffer
    .word 8                 // Value buffer size
    .word 4                 // Request size
    .word 16                // Alignment
    .word 0                 // Framebuffer address (will be updated)
    .word 0                 // End tag
