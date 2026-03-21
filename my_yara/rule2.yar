rule HexAndAll {
    strings:
        $hex1 = { 4D 5A }
        $hex2 = { 50 45 00 00 }
    condition:
        all of ($hex*)
}
