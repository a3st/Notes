<template>
    <div class="note-container">
        <div class="note-header-container">
            <span class="note-title" @mousedown="$emit('click', $event)">{{ title }}</span>

            <div style="display: flex; flex-direction: row; margin-left: auto;">
                <button class="btn-icon" @click="onContextClick($event)">
                    <object style="pointer-events: none;" data="images/ellipsis.svg" width="16" height="16"></object>
                </button>
            </div>
        </div>

        <div class="note-body-container" v-html="description" @mousedown="$emit('click', $event)"></div>
    </div>
</template>

<script>
import {marked} from 'marked'

export default {
    emits: ['click', 'context'],
    props: {
        title: String,
        data: String
    },
    computed: {
        description() {
            return marked(this.data);
        }
    },
    methods: {
        onContextClick(e) {
            this.$emit('context', e);
        }
    }
}
</script>

<style>
.note-container {
    position: relative;
    border-top: 5px solid rgb(227 221 192);
    display: flex; 
    flex-direction: column;
    background-color: rgb(255, 247, 209);
    min-height: 70px;
    max-height: 130px;
}

.note-container:before {
    content: "";
    position: absolute;
    bottom: 0;
    right: 0;
    border-width: 0 16px 16px 0;
    border-style: solid;
    border-color: rgb(227 221 192) rgb(255, 255, 255);
    transform: rotateZ(90deg);
}

.note-container:hover {
    background-color: rgb(238, 231, 195)
}

.note-header-container {
    display: flex;
    height: 30px;
    padding: 5px;
    align-items: center;
}

.note-title {
    display: flex;
    width: 100%;
    justify-content: start;
    align-items: center;
    padding-left: 5px;
    font-weight: bold;
}

.note-body-container {
    display: flex;
    flex-direction: column;
    padding: 5px;
    margin: 5px;
    overflow: hidden;
}

.note-body-container h1 {
    font-size: 16px;
    margin: 2px 0px 0px 0px;
    font-weight: normal;
}

.note-body-container h2 {
    font-size: 14px;
    margin: 2px 0px 0px 0px;
    font-weight: normal;
}

.note-body-container h3 {
    font-size: 12px;
    margin: 2px 0px 0px 0px;
    font-weight: normal;
}

.note-body-container h4 {
    font-size: 10px;
    margin: 2px 0px 0px 0px;
    font-weight: normal;
}

.note-body-container h5 {
    font-size: 8px;
    margin: 2px 0px 0px 0px;
    font-weight: normal;
}

.note-body-container h6 {
    font-size: 6px;
    margin: 2px 0px 0px 0px;
    font-weight: normal;
}

.note-body-container p {
    font-size: 12px;
    margin: 1px 0px 0px 0px;
    font-weight: normal;
}

.note-body-container ol, ul {
    margin: 1px 0px 0px 0px;
}

.note-body-container li {
    font-size: 10px;
}

.note-body-container img {
    width: 50%;
    height: auto;
}
</style>