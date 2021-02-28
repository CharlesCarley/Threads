# --------------------------------------------
# cpy_stack(r12 -> uint64_t*,  r13 -> sizeof(stack) -> uint64_t)
# --------------------------------------------
cpy_stack:
    mov     %rbp,           %r9
    sub     %rsp,           %r9             # size = (RBP - RSP)
    cmp     $0x00,          %r9             # if (size <= 0) goto  cpspe
    jle     cpspd
    add     %r13,           %r12            # &stack[0] + sizeof(stack)/8
    sub     %r9,            %r12            #  stack -= size
cpsps:
    mov     (%rsp, %r9, 1), %r11           
    mov     %r11,           (%r12, %r9, 1)  # stack[r9] = RSP[r9]
    cmp     $0x00,          %r9
    jle     cpspd
    sub     $0x08,          %r9             # size -= 8
    jmp     cpsps
cpspd:
    ret

# --------------------------------------------
#
# set_stack(&pcb.rsp -> uint64_t*, sizeof(stack) -> uint64_t)
#
# --------------------------------------------
.globl set_stack
set_stack:
    mov     0x00(%rdi),   %r12
    mov     %rsi,         %r13
    call    cpy_stack
    mov     %r12,         %rsp
    pop     -0x08(%rsp)
    ret

# --------------------------------------------
# ctx_save(&pcb -> pcb_t, sizeof(stack) -> uint64_t)
# --------------------------------------------
.globl ctx_save
ctx_save:
    mov     %rdi,         %r10
    mov     %rsi,         %r13
    mov     %rbp,         0x30(%r10)
    mov     %rbx,         0x08(%r10)
    mov     %rcx,         0x10(%r10)
    mov     %rdx,         0x18(%r10)
    mov     %rdi,         0x20(%r10)
    mov     %rsi,         0x28(%r10)
    movq    $1,           0x40(%r10)  # Switch the state indicator on.
                                      # Which is just flagging that 
                                      # something has been copied into
                                      # the current pcb_t structure.
    mov     0x00(%r10),   %r12
    call    cpy_stack
    lea     0x08(%rip),    %r11       # return past, the r12 -> 0(%r10)   
    mov     %r11,         0x38(%r10)  
    mov     %r12,         0x00(%r10)
    nop
    nop   # <- return here
    ret

# --------------------------------------------
# ctx_load(&pcb -> pcb_t)
# --------------------------------------------
.globl ctx_load
ctx_load:
    mov     %rdi,           %r10
    mov     0x30(%r10),     %rbp
    mov     0x28(%r10),     %rsi
    mov     0x20(%r10),     %rdi
    mov     0x18(%r10),     %rdx   
    mov     0x10(%r10),     %rcx   
    mov     0x08(%r10),     %rbx
    mov     0x00(%r10),     %rsp
    mov     0x38(%r10),     %rax
    mov     %rax,           0x00(%rsp)
    ret
