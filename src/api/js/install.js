#!/usr/bin/env node
import child_process from "child_process";
import path from 'path';
import fs from 'fs';

const __dirname = path.resolve();

try {
    child_process.execSync(`git clone --recursive --branch clblast https://github.com/tussoftwaredesign/claw-js.git ${__dirname}/node_modules/claw-src`);

    process.chdir(`${__dirname}/node_modules/claw-src`);

    child_process.execSync('mkdir build');

    child_process.execSync(`cmake -S . -B build -GNinja -DCMAKE_BUILD_TYPE=Release`);
    child_process.execSync('cmake --build build -j10');

    const libclaw = 'libclaw.dylib';

    fs.renameSync(`./build/${libclaw}`, `../.bin/${libclaw}`);

    const libclawAbsolutePath = `${__dirname}/node_modules/.bin/${libclaw}`;

    fs.writeFileSync('../claw-js/.env', `LIBCLAW_PATH=${libclawAbsolutePath}`);

    process.chdir(`../..`);
    fs.rmSync('./node_modules/claw-src', {force: true, recursive: true});
} catch (err) {
    console.error(err);
}