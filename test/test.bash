#!/bin/bash
EXEC=build/test

echo "${EXEC}"
${EXEC}
echo "${EXEC} mes --arg0 6"
${EXEC} mes --arg0 6
echo "${EXEC} mes -a 6"
${EXEC} mes -a 6
echo "${EXEC} mes --arg1 6"
${EXEC} mes --arg1 6
echo "${EXEC} mes -a 5ty --arg1 6"
${EXEC} mes -a 5ty --arg1 6
