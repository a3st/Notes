<template>
    <div class="editor-container">
        <div class="header-input-container">
            <input
                type="text"
                placeholder="Придумайте что написать..."
                v-model="title"
                @focus="onFocusInput"
            />
        </div>

        <div v-show="isOpenEditor" class="body-input-container">
            <div
                v-if="isPreview"
                style="display: flex; padding: 10px; height: calc(100% - 80px)"
            >
                <div
                    class="markdown-container"
                    v-html="previewText"
                    @mousedown="onSwitchVisibleEditorClick"
                ></div>
            </div>
            <div
                v-else
                style="display: flex; padding: 10px; height: calc(100% - 80px)"
            >
                <textarea placeholder="Заметка..." v-model="content"></textarea>
            </div>

            <div class="footer-input-container">
                <div
                    style="
                        display: flex;
                        flex-direction: row;
                        align-items: center;
                        width: 100%;
                    "
                >
                    <div style="display: flex; flex-direction: row; gap: 10px">
                        <button
                            title="Предпросмотр"
                            class="btn-icon circle"
                            style="width: 36px; height: 36px"
                            @click="onSwitchVisibleClick"
                        >
                            <img
                                :src="require('../images/eye.svg')"
                                width="20"
                                height="20"
                            />
                        </button>

                        <button
                            v-show="this.id != -1"
                            id="export-btn"
                            title="Экспорт"
                            class="btn-icon circle"
                            style="width: 36px; height: 36px"
                            @click="onExportClick"
                        >
                            <img
                                :src="require('../images/file-export.svg')"
                                width="20"
                                height="20"
                            />
                        </button>
                    </div>
                    <div
                        style="
                            display: flex;
                            flex-direction: row;
                            margin-left: auto;
                        "
                    >
                        <button
                            class="btn-text"
                            @click="onSaveClick"
                            style="font-weight: bold"
                            v-bind:disabled="
                                !isChanged || this.title.length == 0
                            "
                        >
                            Сохранить
                        </button>
                        <button
                            class="btn-text"
                            @click="onCloseClick"
                            style="font-weight: bold"
                        >
                            Закрыть
                        </button>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import { marked } from "marked";
import { ctxmenu } from "ctxmenu";
import $ from "jquery";

export default {
    emits: ["save"],
    data() {
        return {
            isOpenEditor: false,
            isPreview: false,
            isChanged: false,
            content: "",
            title: "",
            id: -1,
        };
    },
    computed: {
        previewText() {
            return marked(this.content);
        },
    },
    watch: {
        content: {
            handler(value, oldValue) {
                this.isChanged = true;
            },
        },
        title: {
            handler(value, oldValue) {
                this.isChanged = true;
            },
        },
    },
    methods: {
        onFocusInput(e) {
            $(".header-input-container input").attr("placeholder", "Заголовок");

            this.isOpenEditor = true;
        },
        onCloseClick(e) {
            $(".header-input-container input").attr(
                "placeholder",
                "Придумайте что написать..."
            );

            this.title = "";
            this.content = "";
            this.isOpenEditor = false;
            this.isPreview = false;
            this.id = -1;
        },
        onSaveClick(e) {
            webview
                .invoke(
                    "saveNote",
                    this.id,
                    this.title,
                    btoa(unescape(encodeURIComponent(this.content)))
                )
                .then((id) => (this.id = id));
            this.$emit("save", e);
            this.isChanged = false;
        },
        onExportClick(e) {
            e.stopPropagation();
            ctxmenu.show(
                [
                    { text: "Экспорт" },
                    {
                        text: ".TXT",
                        action: () =>
                            webview.invoke("exportNote", this.id, "txt"),
                    },
                ],
                e.target
            );
        },
        open(preview) {
            this.isOpenEditor = true;
            this.isPreview = preview;
        },
        isOpen() {
            return this.isOpenEditor;
        },
        setID(id) {
            this.id = id;
        },
        setTitle(title) {
            this.title = title;
            this.isChanged = false;
        },
        setContent(content) {
            this.content = content;
            this.isChanged = false;
        },
        onSwitchVisibleClick(e) {
            this.isPreview = !this.isPreview;
        },
        onSwitchVisibleEditorClick(e) {
            const containerElement = $(".markdown-container");
            if (
                e.offsetX >= containerElement.width() - 15 ||
                e.offsetY >= containerElement.height() - 15
            ) {
                return;
            }
            this.isPreview = false;
        },
    },
};
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

.markdown-container {
    display: flex;
    flex-direction: column;
    width: 100%;
    height: 100%;
    cursor: text;
    overflow-y: auto;
    overflow-x: auto;
}
</style>