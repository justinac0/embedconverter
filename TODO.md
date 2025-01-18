# TODO

```C
// EMBEDCONVERTER
// -- Supported Types ---------------------------------------
// These should be able to convert into eachother. 
// BINARY_NUMERIC_DATA
//  > HEX
//  > DEC
//  > BIN
// *> OCT
//
// POSSIBLE EXTENSION
// -- Add more tools ---------------------------------------
//  CRC
//  Encryption/Decryption
//  Different Types of Hashing Algorithms
// 
// -- Questions --------------------------------------------
//  > How do we represent BINARY_NUMERIC_DATA.
//  > How should the front end simplify the conversion process so that.
//    relavant information is shown on conversions.
//  > Should we handle file uploads.
//  > What do we want it (UI) to look like.
//  > What types can't convert to other types.
//  > How can market / make profit from this webapp (buy me a coffee).
// 
```

## MVP

- [ ] Represent BINARY_NUMERIC_DATA and display it in HTML (01-18-2025)
- [ ] Add UI selection to chose what BINARY_NUMERIC_DATA you would like to input and the requested output.

## Extras

## Notes

- To convert strings returned from wasm use `UTF8ToString(...)`, where the args
are a function that returns a `char*`
