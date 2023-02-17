<template>
    <div class="inputBox shadow">
        <span>DPOT (AD5160) 설정값</span>
        <input type="number" min="0" max="255" v-model.number="valueDpotSet">
        <span class="dpotSetContainer" v-on:click="onClickSetValue">
            <i class="dpotSetBtn fa-solid fa-gear" aria-hidden="true"></i>
        </span>
    </div>
</template>

<script>
export default {
    data() {
        return {
            valueDpotSet: 0
        }
    },
    beforeMount: function() {
        this.$axios({
            method: "get",
            url: "/api/dpot"
        })
        .then(response => {
            console.log(response.data, response.data.raw_value, typeof(response.data.raw_value));
            this.valueDpotSet = response.data.raw_value;
        })
        .catch(error => {
            console.log(error);
            this.valueDpotSet = 0;
        })
    },
    methods: {
        onClickSetValue() {
            console.log(this.valueDpotSet);
            this.$axios({
                method: "post",
                url: "/api/dpot",
                data: JSON.stringify({
                    raw_value: this.valueDpotSet
                }),
                headers: {
                    "Content-Type": "application/json; charset=utf-8"
                },
                timeout: 5000
            })
            .then(response => {
                
            })
            .catch(error => {
                console.log(error);
            })
        }
    }
}
</script>

<style>
    input:focus {
        outline: none;
    }
    .inputBox {
        background: white;
        height: 50px;
        line-height: 50px;
        border-radius: 5px;
        font-size: 20px;
    }
    .inputBox input {
        border-style: groove;
        font-size: 20px;
        width: 50px;
    }
</style>