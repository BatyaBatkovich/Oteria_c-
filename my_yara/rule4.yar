rule ComplexMonster {
    strings:
        $str1 = "malware"
        $str2 = "backdoor"
        $str3 = "password"
        $hex1 = { 4D 5A }
        $hex2 = { 50 45 }
        $reg1 = /192\.168\.[0-9]{1,3}\.[0-9]{1,3}/
    condition:
        all of ($hex*) and ( ($str1 and not $str2) or ($str3 and $reg1) ) or any of ($str*)
}
