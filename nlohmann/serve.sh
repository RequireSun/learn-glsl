#!/usr/bin/env bash
BASEDIR="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

serve ${BASEDIR}/ -p 8877 -c ${BASEDIR}/serve.json -C
