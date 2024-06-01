<template>
    <div class="editor-container">
        <div class="header-input-container">
            <input type="text" placeholder="Придумайте о чем написать..." @focus="onFocusInput($event)" />
        </div>

        <div v-if="isOpenEditor" class="body-input-container">
            <textarea style="padding: 10px;" placeholder="Заметка..."></textarea>

            <div class="footer-input-container">
                <div style="display: flex; flex-direction: row; align-items: center; width: 100%;">
                    <div style="display: flex; flex-direction: row; gap: 10px;">
                        <button title="Предпросмотр" class="btn-icon circle" style="width: 36px; height: 36px;">
                            <object style="pointer-events: none;" data="images/eye.svg" width="20" height="20"></object>
                        </button>

                        <button title="Экспорт" class="btn-icon circle" style="width: 36px; height: 36px;" @click="onExportClick($event)">
                            <object style="pointer-events: none;" data="images/file-export.svg" width="20" height="20"></object>
                        </button>

                        <div v-if="isOpenExport" class="expand-inline-menu" style="background-color: rgb(245, 245, 220);">
                            <button title="PDF" class="btn-icon circle" style="width: 36px; height: 36px;" @click="">
                                <object style="pointer-events: none;" data="images/pdf.svg" width="20" height="20"></object>
                            </button>

                            <button title="DOCX" class="btn-icon circle" style="width: 36px; height: 36px;" @click="">
                                <object style="pointer-events: none;" data="images/doc.svg" width="20" height="20"></object>
                            </button>

                            <button title="TXT" class="btn-icon circle" style="width: 36px; height: 36px;" @click="">
                                <object style="pointer-events: none;" data="images/txt.svg" width="20" height="20"></object>
                            </button>
                        </div>
                    </div>
                    <div style="display: flex; flex-direction: row; margin-left: auto;">
                        <button class="btn-text" @click="" style="font-weight: bold;">Сохранить</button>
                        <button class="btn-text" @click="onCloseClick($event)" style="font-weight: bold;">Закрыть</button>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import { toRaw } from 'vue';
import $ from 'jquery';

export default {
    data() {
        return {
            isOpenEditor: false,
            isOpenExport: false
        }
    },
    mounted() {
        $(document).bind('click', e => {
            if($(e.target).closest('.editor-container').length == 0) {
                $('.header-input-container input').attr('placeholder', 'Придумайте о чем написать...');
                this.isOpenEditor = false;
                this.isOpenExport = false;
            }
        });
    },
    methods: {
        onFocusInput(e) {
            $('.header-input-container input').attr('placeholder', 'Заголовок');
            this.isOpenEditor = true;
        },
        onCloseClick(e) {
            $('.header-input-container input').attr('placeholder', 'Придумайте о чем написать...');
            this.isOpenEditor = false;
            this.isOpenExport = false;
        },
        onExportClick(e) {
            this.isOpenExport = !this.isOpenExport;
        }
    }
}
</script>

<style>
.editor-container {
    display: flex;
    flex-direction: column;
    border-radius: 10px;
    background-color: white; 
    outline: rgb(78, 78, 78) solid 1.5px;
    box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.137);
}

.header-input-container {
    display: flex;
    height: 45px;
    padding-left: 10px;
    padding-right: 10px;
}

.footer-input-container {
    border-top: 1px solid rgb(221, 221, 221);
    display: flex;
    height: 40px;
    padding: 10px;
}

.body-input-container {
    display: flex;
    flex-direction: column;
    height: 400px;
}
</style>