
pub struct QYEncryption {
    i: u8,
    j: u8,
    state: [u8; 256]
}

impl QYEncryption {
    pub fn new(key: &[u8]) -> QYEncryption {
        assert!(key.len() >= 1 && key.len() <= 256);
        let mut qyencryption = QYEncryption { i: 0, j: 0, state: [0; 256] };
        for (i, x) in qyencryption.state.iter_mut().enumerate() {
            *x = i as u8;
        }
        let mut j: u8 = 0;
        for i in 0..256 {
            j = j.wrapping_add(qyencryption.state[i]).wrapping_add(key[i % key.len()].wrapping_mul(key[(i + 1) % key.len()]));
            qyencryption.state.swap(i, j as usize);
        }
        qyencryption
    }

    pub fn encrypt(&mut self, input: &[u8], output: &mut [u8]) {
        for (i, x) in input.iter().enumerate() {
            output[i] = self.next() ^ *x
        }
    }

    fn next(&mut self) -> u8 {
        self.i = self.i.wrapping_add(1); // we want this to wrap after 255
        self.j = self.j.wrapping_add(self.state[self.i as usize]); // we want this to wrap after 255
        self.state.swap(self.i as usize, self.j as usize);
        let k = self.state[(self.state[self.i as usize].wrapping_add(self.state[self.j as usize])) as usize];
        k
    }
}
