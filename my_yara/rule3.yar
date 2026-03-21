rule RegexAndAny {
    strings:
        $regex1 = /error_[0-9]+/
        $str1 = "fatal"
        $str2 = "panic"
        $str3 = "warning"
    condition:
        $regex1 and not any of ($str*)
}
