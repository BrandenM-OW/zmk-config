# zmk-config: Typeractive Corne (MX, wireless)

ZMK firmware for the MX Corne: nice!nano v2 controllers, nice!view screens, ZMK v0.3. GitHub builds it on every push.

The keymap is the same Colemak-DH layout as the wired Choc Corne. **Don't edit `config/corne.keymap` by hand**: it is
generated from the Vial keymap in the `corne` repo:

```
cd ..\corne
python make_zmk.py        # writes mx\Colemak-DH-V1.keymap, mx\Colemak-DH-V2.keymap and copies V2 here
```

Then commit and push this repo.

## Flashing

1. Push, then open the repo's **Actions** tab and wait for the run to go green (about 3-5 minutes).
2. Download the **firmware** artifact and unzip it: `corne_left-....uf2` and `corne_right-....uf2`.
3. Plug in the left half with USB and double-tap its reset button. A drive called `NICENANO` appears. Copy
   `corne_left...uf2` onto it; it restarts by itself when done.
4. Same for the right half with `corne_right...uf2`.

Instead of double-tapping reset, you can also hold both inner thumbs (layer 3) and press the top outer key of that half.

## Layer 3 (hold both inner thumbs)

```
 BOOT  BT0  BT1  BT2  BT3  BT4        .    .    .    .    .  BOOT
 UNLK   .    .    .    .    .         .    .    .    .    .    .
 BTCLR USB  BLE   .    .    .         .    .    .    .    .    .
```

- **BT0-BT4**: switch between up to 5 paired computers. **BTCLR** forgets the pairing of the current slot.
- **USB / BLE**: send keys over the cable or Bluetooth when both are connected.
- **UNLK**: unlocks ZMK Studio so it can change keys live.
- **BOOT**: flashing mode for that half.

## ZMK Studio

Studio changes are stored on the keyboard and **override this keymap**. After flashing a new keymap from here, open
https://zmk.studio, connect, unlock, and use **Restore Stock Settings** so the board uses the file again. Make
lasting changes in the `.vil` + `make_zmk.py`, and use Studio only for quick experiments.

## If the halves stop talking or a computer won't pair

Flash `settings_reset` to both halves, then the normal files again, then re-pair (remove "Corne" from the computer's
Bluetooth list first).
