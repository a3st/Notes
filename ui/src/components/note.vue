<template>
    <div class="note-container">
        <div class="note-header-container">
            <span class="note-title">{{ title }}</span>

            <div style="display: flex; flex-direction: row; margin-left: auto;">
                <div v-if="isOpenExt" class="expand-inline-menu" style="background-color: rgb(227, 221, 192);">
                    <button title="Удалить" class="btn-icon circle" style="width: 22px; height: 22px;" @click="">
                        <object style="pointer-events: none;" data="images/trash.svg" width="10" height="10"></object>
                    </button>
                </div>
                <button class="btn-icon" @click="onOpenExtClick($event)">
                    <object style="pointer-events: none;" data="images/ellipsis.svg" width="16" height="16"></object>
                </button>
            </div>
        </div>

        <div class="note-body-container">1</div>
    </div>
</template>

<script>
export default {
    props: {
        title: String,
        data: String
    },
    data() {
        return {
            isOpenExt: false
        }
    },
    methods: {
        onOpenExtClick(e) {
            this.isOpenExt = !this.isOpenExt;
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
    padding: 5px;
}
</style>