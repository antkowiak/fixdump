#!/bin/bash
echo "    \"${2}\": {"
cat $1 |sed -E "s/\"/'/g" |sed -E 's/^(.*) = (.*)$/"\1": "\2",/g' |sort |sed -E '/^$/d' |sed -E ':a;N;$! ba;s/,$//g' |sed -E 's/^(.*)$/      \1/g'
echo "    },"

