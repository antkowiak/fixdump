#!/bin/bash
cat $1 |sed -E 's/^(.*) = (.*)$/"\1": "\2",/g' |sort |sed -E '/^$/d' |sed -E ':a;N;$! ba;s/,$//g'

