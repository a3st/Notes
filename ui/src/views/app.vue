<template>
    <div class="wrapper-container">
        <editor></editor>

        <div v-if="isLoading" class="notegr-container">
            <note title="Заметка 1"></note>
            <note title="Заметка 2"></note>
            <note title="Заметка 3"></note>
            <note title="Заметка 4"></note>
            <note title="Заметка 5"></note>
            <note title="Заметка 6"></note>
        </div>

        <div v-else class="notegr-loading-container">
            <div class="loader"></div>
            <span>Загрузка заметок...</span>
        </div>
    </div>
</template>

<script>
import $ from 'jquery';

import NoteComponent from '../components/note.vue';
import EditorComponent from '../components/editor.vue';

export default {
    components: {
        'note': NoteComponent,
        'editor': EditorComponent
    },
    data() {
        return {
            isLoading: true
        }
    },
    created() {
        $(window).on('resize', e => {
            this.updateNoteGroupHeight(e.target.outerHeight);
        });
    },
    destroyed() {
        $(window).off('resize');
    },
    mounted() {
        
    },
    methods: {
        updateNoteGroupHeight(windowHeight) {
            $('.notegr-container').css('height', windowHeight - ($('.editor-container').height() + 80));
        }
    }
}
</script>

<style>
@font-face {
    font-family: 'Roboto', sans-serif;
    src: url('../fonts/Roboto-Regular.ttf') format('truetype');
    font-weight: 400;
    font-style: normal;
}

@font-face {
    font-family: 'Roboto', sans-serif;
    src: url('../fonts/Roboto-Bold.ttf') format('truetype');
    font-weight: bold;
    font-style: normal;
}

@font-face {
    font-family: 'Roboto', sans-serif;
    src: url('../fonts/Roboto-Medium.ttf') format('truetype');
    font-weight: 500;
    font-style: normal;
}

.loader {
  width: 50px;
  aspect-ratio: 1;
  border-radius: 50%;
  border: 8px solid;
  border-color: #000 #0000;
  animation: l1 1s infinite;
}

@keyframes l1 {
    to {
        transform: rotate(.5turn)
    }
}

.notegr-container {
    display: flex; 
    flex-direction: column;
    gap: 20px; 
    padding: 10px; 
    margin-top: 10px; 
    overflow-y: scroll;
    overflow-x: hidden;
}

.notegr-loading-container {
    display: flex;
    flex-direction: column;
    width: 100%;
    margin-top: 50px;
    align-items: center;
    justify-content: center;
    gap: 20px;
}

.wrapper-container {
    padding: 20px;
}

.btn-text {
    outline: none;
    border: none;
    background: none;
    padding: 10px 15px 10px 15px;
}

.btn-text:hover {
    border-radius: 6px;
    background-color: rgba(236, 236, 236, 0.76);
}

.btn-icon {
    background: none;
    outline: none;
    border: none;
}

.btn-icon.circle:hover {
    border-radius: 30px;
    background-color: rgba(150, 150, 150, 0.26);
}

.expand-inline-menu {
    display: inline-flex;
    border-radius: 6px;
}

body {
    margin: 0;
    padding: 0;
    overflow-y: hidden;
    overflow-x: hidden;
    font-family: 'Roboto', sans-serif;
}

textarea {
    width: 100%;
    height: 100%;
    outline: none;
    border: none;
    resize: none;
    font-size: 14px;
}

input {
    outline: none;
    border: none;
    font-size: 18px;
    width: 100%;
}
</style>