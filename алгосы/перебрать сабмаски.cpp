for (int mask = 0; mask < (1 << n); ++mask) {
    for (int submask = mask; ; submask = ((submask - 1) & mask)) {
        // работаем с submask
        
        if (submask == 0) {
            break;
        }
    }
}